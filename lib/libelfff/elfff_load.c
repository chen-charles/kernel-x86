#include    "libelfff.h"

bool elfff_header_validate(elfff_ctx *ctx)
{
    if (!ctx->header)
    {
        elfff_dprintf("header is null. terminate. \n");
        return false;
    }
        
    if (ctx->header->e_ident[EI_MAG0] != ELFMAG0 || 
        ctx->header->e_ident[EI_MAG1] != ELFMAG1 ||
        ctx->header->e_ident[EI_MAG2] != ELFMAG2 ||
        ctx->header->e_ident[EI_MAG3] != ELFMAG3)
        return false;

    if (ctx->header->e_ident[EI_CLASS] != 
#ifdef __x86_64__
        ELFCLASS64
#else
        ELFCLASS32
#endif
    )
        return false;

    if (ctx->header->e_ident[EI_VERSION] != EV_CURRENT)
        return false;
    
    if (ctx->header->e_type != ET_EXEC && ctx->header->e_type != ET_DYN)
    {
        elfff_dprintf("libelfff currently only supports loading ET_EXEC and ET_DYN ELFs. \n");
        return false;
    }

    elfff_dprintf("[SKIP] e_machine\n");

    if (ctx->header->e_phoff == 0 || ctx->header->e_phnum == 0)
    {
        elfff_dprintf("program header does not exist. terminate. \n");
        return false;
    }

    return true;
}

#ifndef elf_
#ifdef __x86_64__
#define elf_(name) Elf64_ ## name
#define elf_ab(a, b) a ## 64 ## b
#else
#define elf_(name) Elf32_ ## name
#define elf_ab(a, b) a ## 32 ## b
#endif
#endif

static inline elf_(Phdr*) get_phdr(elfff_ctx* ctx, size_t index)
{
    return ((elf_(Phdr*))((ctx->raw).ptr + (ctx->header)->e_phoff)) + index;
}

static inline elf_(Shdr)* get_shdr(elfff_ctx* ctx, size_t index)
{
    return ((elf_(Shdr*))((ctx->raw).ptr + (ctx->header)->e_shoff)) + index;
}

elf_(Addr) elfff_get_actual_address(elfff_ctx* ctx, elf_(Addr) p_vaddr)
{
    for(int i = 0; i < ctx->header->e_phnum; i++)
    {
        elf_(Phdr*) phdr = get_phdr(ctx, i);
        if (phdr->p_vaddr <= p_vaddr && 
            phdr->p_vaddr + phdr->p_memsz > p_vaddr)
            return p_vaddr - phdr->p_vaddr + phdr->p_paddr;
    }
    
    return 0;
}

elf_(Addr) elfff_get_symbol_value(elfff_ctx* ctx, elf_(Word) sec_indx, elf_(Word) entry_indx)
{
    if(sec_indx == SHN_UNDEF || entry_indx == SHN_UNDEF) return 0;
    elf_(Sym) symbol = ((elf_(Sym*))((uintptr_t)(ctx->raw.ptr) + get_shdr(ctx, sec_indx)->sh_offset))[entry_indx];
    if(symbol.st_shndx == SHN_UNDEF) return 0;
    switch (symbol.st_shndx)
    {
        case SHN_UNDEF:
            return 0;
        case SHN_ABS:
            return symbol.st_value;
        default:
            return symbol.st_value;
    }
}

ELFFF_STATUS elfff_load(elfff_ctx* ctx)
{
    #ifdef __x86_64__
    elfff_dprintf("running in x86_64 mode\n");
    #else
    elfff_dprintf("running in x86 mode\n");
    #endif
    
    ctx->header = ((ctx->raw).ptr); 
    if (!elfff_header_validate(ctx))
        return ELFFF_HEADER_INVALID;

    ctx->pheader = ((ctx->raw).ptr + (ctx->header)->e_phoff);

    ctx->sheader = ((ctx->raw).ptr + (ctx->header)->e_shoff);
    
    // String table
    if (ctx->header->e_shstrndx == SHN_UNDEF) ctx->strtab = NULL;
    else ctx->strtab = (char*)ctx->header + (ctx->sheader + ctx->header->e_shstrndx)->sh_offset;

    // Load Elf Phys Headers
    elfff_page_property pp;
    void* mapped;
    for (size_t i=0; i<ctx->header->e_phnum; i++)
    {
        elfff_dprintf("pheader %d: type=%d\n", (int)i, (int)(ctx->pheader->p_type));
        switch(ctx->pheader->p_type)
        {
            case PT_LOAD:
                pp.read = ctx->pheader->p_flags & PF_R;
                pp.write = ctx->pheader->p_flags & PF_W;
                pp.execute = ctx->pheader->p_flags & PF_X;
                mapped = elfff_mmap(ctx->pheader->p_vaddr, ctx->pheader->p_memsz, &pp);
                if (!mapped)
                    return ELFFF_MMAP_FAIL;
                memcpy(mapped, (void*)(ctx->raw.ptr + ctx->pheader->p_offset), ctx->pheader->p_filesz);
                if (ctx->pheader->p_filesz < ctx->pheader->p_memsz)
                    memset((void*)((uintptr_t)mapped) + ctx->pheader->p_filesz, 0, ctx->pheader->p_memsz - ctx->pheader->p_filesz);
                ctx->pheader->p_paddr = (uintptr_t)mapped;
                elfff_dprintf("loaded at %d\n", (int)(ctx->pheader->p_paddr));
                break;
            case PT_DYNAMIC:
                break;      
            default:
                elfff_dprintf("Phdr type=%d not implemented\n", (int)(ctx->pheader->p_type));
        }
        
        ctx->pheader++;
    }

    for (size_t i = 0; i < ctx->header->e_shnum; i++)
    {
        if(ctx->sheader->sh_type == SHT_REL)
        {
            // sh_info -> section index to be relocated
            // sh_link -> symtab for this relocation section
            elf_(Shdr*) symtab = get_shdr(ctx, ctx->sheader->sh_link);
            elf_(Shdr*) target = get_shdr(ctx, ctx->sheader->sh_info);
            elf_(Rel*) rel = (ctx->raw).ptr + ctx->sheader->sh_offset;

			// Process each entry in the table
            for(size_t j = 0; j < ctx->sheader->sh_size / ctx->sheader->sh_entsize; j++)
            {
                rel[j].r_offset = elfff_get_actual_address(ctx, rel[j].r_offset);
                if (rel[j].r_offset == 0) return ELFFF_VADDR_INVALID;

                elf_(Addr) symval = elfff_get_symbol_value(ctx, ctx->sheader->sh_link, elf_ab(ELF, _R_SYM)(rel[j].r_info));
                switch (elf_ab(ELF, _R_TYPE)(rel[j].r_info))
                {
                    case R_386_32:
                        *(uintptr_t*)(rel[j].r_offset) = elfff_get_actual_address(ctx, *(uintptr_t*)(rel[j].r_offset));
                        break;
                    case R_386_PC32:
                        // * r_offset - symval + actual symbol value
                        *(uintptr_t*)(rel[j].r_offset)
                            = elfff_get_actual_address(ctx, symval) - rel[j].r_offset - sizeof(uintptr_t);
                        break;
                    default:
                        ;
                }
                

            }
        }
        ctx->sheader ++;
    }

    ctx->prog_entry = elfff_get_actual_address(ctx, ctx->header->e_entry);
    return ELFFF_SUCCESS;
}


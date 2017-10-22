#include    "libelfff.h"

bool elf_header_validate(elfff_ctx *ctx)
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
#undef bochsdbg_bp_eax
#define bochsdbg_bp() __asm__ volatile ( "xchg bx, bx" )
#define bochsdbg_bp_eax(eax) \
{   \
    __asm__ volatile ("push eax");  \
    __asm__ volatile ("mov eax, %0" : : ""((long)(eax))); \
    bochsdbg_bp();  \
    __asm__ volatile ("pop eax");   \
}
ELFFF_STATUS elfff_load(elfff_ctx* ctx)
{
    #ifdef __x86_64__
    elfff_dprintf("running in x86_64 mode\n");
    #else
    elfff_dprintf("running in x86 mode\n");
    #endif
    
    ctx->header = (
        #ifdef __x86_64__
                Elf64_Ehdr*
        #else
                Elf32_Ehdr*
        #endif
            )((ctx->raw).ptr); 
    if (!elf_header_validate(ctx))
        return ELFFF_HEADER_INVALID;

    ctx->pheader = (
        #ifdef __x86_64__
                Elf64_Phdr*
        #else
                Elf32_Phdr*
        #endif
            )((ctx->raw).ptr + (ctx->header)->e_phoff);

    elfff_page_property pp;
    void* mapped;
    for (size_t i=0; i<ctx->header->e_phnum; i++)
    {
        elfff_dprintf("parsing pheader %d: type=%d\n", i, ctx->pheader->p_type);
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
                break;
            case PT_DYNAMIC:
                break;      
            default:
                elfff_dprintf("[SKIP] not implemented\n");
        }
        
        ctx->pheader = (
            #ifdef __x86_64__
                    Elf64_Phdr*
            #else
                    Elf32_Phdr*
            #endif
                )((uintptr_t)ctx->pheader + ctx->header->e_phentsize);
    }

    return ELFFF_SUCCESS;
}

#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>

#include    <klib_ad/x86/gdt.h>

#include    "include/memloc.h"
#include    "include/kinit_alloc.h"

//ptr align 16
uintreg_t gdt_init()
{
    uintptr_t pPTR = (uintptr_t)kinit_aligned_alloc(6, 16);
	uint16_t *gdtlen = (uint16_t*)pPTR;
	uint32_t *gdtaddr =  (uint32_t*)(pPTR+2);
    
    *gdtlen = sizeof(DESCRIPTOR)*16;
	*gdtaddr = PM_GDT_PTR;

	int p=0;

	// Entry 0 -> empty
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0, 0);

	// Entry 1 -> 32-bit Ring 0 Code E/R, Accessed, conforming, shared resources	-> kernel code segment
        // user-mode can access this segment with RPL 3
        // kernel-mode could not access user-mode code/data
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL0 | DA_CCOR);

	// Entry 2 -> 32-bit Ring 0 Code E/R, Accessed, non-conforming, critical session	-> kernel code segment
	// access in the same ring ONLY, restrict ALL access across rings
    init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL0 | DA_CR);

	// Entry 3 -> 32-bit Ring 0 Data R/W, Accessed	-> kernel data segment
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL0 | DA_DRWA);
	
	// Entry 4 -> 32-bit Ring 3 Code E/R			-> user code segment
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL3 | DA_CCOR);

	// Entry 5 -> 32-bit Ring 3 Data R/W, Accessed	-> user data segment
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL3 | DA_DRWA);

	// Entry 6 -> 32-bit Ring 1 Code E/R			-> kernel-service code segment
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL1 | DA_CCOR);

	// Entry 7 -> 32-bit Ring 1 Data R/W, Accessed	-> kernel-service data segment
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL1 | DA_DRWA);

	// Entry 8 -> 32-bit Ring 2 Code E/R			-> user-service code segment
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL2 | DA_CCOR);

	// Entry 9 -> 32-bit Ring 2 Data R/W, Accessed	-> user-service data segment
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0xffffffff, DA_32 | DA_LIMIT_4K | DA_DPL2 | DA_DRWA);

	// Entry 10 -> TSS
    // init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0, 0);
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, PM_TSS_PTR, PM_TSS_PTR + sizeof(TSS)-1, DA_386TSS);

	// Entry 11 ~ 15 -> empty
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0, 0);
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0, 0);
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0, 0);
	init_pm_desc((DESCRIPTOR*)*gdtaddr + p++, 0, 0, 0);

	return pPTR;
}

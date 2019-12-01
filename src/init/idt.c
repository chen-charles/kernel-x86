#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>

#include    <klib_ad/x86/idt.h>
#include    <klib_ad/x86/instruction.h>

#include    "include/memloc.h"
#include	"include/interrupt.h"
#include	"include/kinit_alloc.h"



uintreg_t idt_init();

int stub_intr(void* esp, uint32_t int_id)
{
    return 0;
}

uintreg_t c_idt_init()
{
    //if an interrupt is launched and no predetermined routines is there to handle,
    //the C-handler will try to index the interrupt redirect table(pIHTable)
    //if the function pointer is not NULLPTR, the function will be called
    //in __cdecl calling convention with param (void* esp, uint32_t int_id)
    //
    //the redirect table is init-ed here
    //internal / critical interrupt routines are pre-determined
    //they will be redirected from the C-handler before indexing the table
    //just be aware of that

    memset((void*)pIHTable, 0, sizeof(uintptr_t)*256);
	*(((uintptr_t*)pIHTable)+INT_VEC_APIC_TIMER) = (uintptr_t)(&stub_intr);
    return idt_init();;
}

uintreg_t idt_init()
{
	uint16_t *idtlen = (uint16_t*)SHARED_IDTR;
	uint32_t *idtaddr = (uint32_t*)(SHARED_IDTR + 2);
	*idtaddr = pIDTable;
	*idtlen = sizeof(GATE)*256;
	init_idt_desc((GATE*)(*idtaddr) + 0, &int_handler_0, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 1, &int_handler_1, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 2, &int_handler_2, 0, 0x10);

	// INT_VEC_BP: allow usermode breakpoints
	init_idt_desc((GATE*)(*idtaddr) + 3, &int_handler_3, 3, 0x10);

	init_idt_desc((GATE*)(*idtaddr) + 4, &int_handler_4, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 5, &int_handler_5, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 6, &int_handler_6, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 7, &int_handler_7, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 8, &int_handler_8, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 9, &int_handler_9, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 10, &int_handler_10, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 11, &int_handler_11, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 12, &int_handler_12, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 13, &int_handler_13, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 14, &int_handler_14, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 15, &int_handler_15, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 16, &int_handler_16, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 17, &int_handler_17, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 18, &int_handler_18, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 19, &int_handler_19, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 20, &int_handler_20, 3, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 21, &int_handler_21, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 22, &int_handler_22, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 23, &int_handler_23, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 24, &int_handler_24, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 25, &int_handler_25, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 26, &int_handler_26, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 27, &int_handler_27, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 28, &int_handler_28, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 29, &int_handler_29, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 30, &int_handler_30, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 31, &int_handler_31, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 32, &int_handler_32, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 33, &int_handler_33, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 34, &int_handler_34, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 35, &int_handler_35, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 36, &int_handler_36, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 37, &int_handler_37, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 38, &int_handler_38, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 39, &int_handler_39, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 40, &int_handler_40, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 41, &int_handler_41, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 42, &int_handler_42, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 43, &int_handler_43, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 44, &int_handler_44, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 45, &int_handler_45, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 46, &int_handler_46, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 47, &int_handler_47, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 48, &int_handler_48, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 49, &int_handler_49, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 50, &int_handler_50, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 51, &int_handler_51, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 52, &int_handler_52, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 53, &int_handler_53, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 54, &int_handler_54, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 55, &int_handler_55, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 56, &int_handler_56, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 57, &int_handler_57, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 58, &int_handler_58, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 59, &int_handler_59, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 60, &int_handler_60, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 61, &int_handler_61, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 62, &int_handler_62, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 63, &int_handler_63, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 64, &int_handler_64, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 65, &int_handler_65, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 66, &int_handler_66, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 67, &int_handler_67, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 68, &int_handler_68, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 69, &int_handler_69, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 70, &int_handler_70, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 71, &int_handler_71, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 72, &int_handler_72, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 73, &int_handler_73, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 74, &int_handler_74, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 75, &int_handler_75, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 76, &int_handler_76, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 77, &int_handler_77, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 78, &int_handler_78, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 79, &int_handler_79, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 80, &int_handler_80, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 81, &int_handler_81, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 82, &int_handler_82, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 83, &int_handler_83, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 84, &int_handler_84, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 85, &int_handler_85, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 86, &int_handler_86, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 87, &int_handler_87, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 88, &int_handler_88, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 89, &int_handler_89, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 90, &int_handler_90, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 91, &int_handler_91, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 92, &int_handler_92, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 93, &int_handler_93, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 94, &int_handler_94, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 95, &int_handler_95, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 96, &int_handler_96, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 97, &int_handler_97, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 98, &int_handler_98, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 99, &int_handler_99, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 100, &int_handler_100, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 101, &int_handler_101, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 102, &int_handler_102, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 103, &int_handler_103, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 104, &int_handler_104, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 105, &int_handler_105, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 106, &int_handler_106, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 107, &int_handler_107, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 108, &int_handler_108, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 109, &int_handler_109, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 110, &int_handler_110, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 111, &int_handler_111, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 112, &int_handler_112, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 113, &int_handler_113, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 114, &int_handler_114, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 115, &int_handler_115, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 116, &int_handler_116, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 117, &int_handler_117, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 118, &int_handler_118, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 119, &int_handler_119, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 120, &int_handler_120, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 121, &int_handler_121, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 122, &int_handler_122, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 123, &int_handler_123, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 124, &int_handler_124, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 125, &int_handler_125, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 126, &int_handler_126, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 127, &int_handler_127, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 128, &int_handler_128, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 129, &int_handler_129, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 130, &int_handler_130, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 131, &int_handler_131, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 132, &int_handler_132, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 133, &int_handler_133, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 134, &int_handler_134, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 135, &int_handler_135, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 136, &int_handler_136, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 137, &int_handler_137, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 138, &int_handler_138, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 139, &int_handler_139, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 140, &int_handler_140, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 141, &int_handler_141, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 142, &int_handler_142, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 143, &int_handler_143, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 144, &int_handler_144, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 145, &int_handler_145, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 146, &int_handler_146, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 147, &int_handler_147, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 148, &int_handler_148, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 149, &int_handler_149, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 150, &int_handler_150, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 151, &int_handler_151, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 152, &int_handler_152, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 153, &int_handler_153, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 154, &int_handler_154, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 155, &int_handler_155, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 156, &int_handler_156, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 157, &int_handler_157, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 158, &int_handler_158, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 159, &int_handler_159, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 160, &int_handler_160, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 161, &int_handler_161, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 162, &int_handler_162, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 163, &int_handler_163, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 164, &int_handler_164, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 165, &int_handler_165, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 166, &int_handler_166, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 167, &int_handler_167, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 168, &int_handler_168, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 169, &int_handler_169, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 170, &int_handler_170, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 171, &int_handler_171, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 172, &int_handler_172, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 173, &int_handler_173, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 174, &int_handler_174, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 175, &int_handler_175, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 176, &int_handler_176, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 177, &int_handler_177, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 178, &int_handler_178, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 179, &int_handler_179, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 180, &int_handler_180, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 181, &int_handler_181, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 182, &int_handler_182, 0, 0x10);

	// INT_VEC_SYSCALL: allow usermode access
	init_idt_desc((GATE*)(*idtaddr) + 183, &int_handler_183, 3, 0x10);

	init_idt_desc((GATE*)(*idtaddr) + 184, &int_handler_184, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 185, &int_handler_185, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 186, &int_handler_186, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 187, &int_handler_187, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 188, &int_handler_188, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 189, &int_handler_189, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 190, &int_handler_190, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 191, &int_handler_191, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 192, &int_handler_192, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 193, &int_handler_193, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 194, &int_handler_194, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 195, &int_handler_195, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 196, &int_handler_196, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 197, &int_handler_197, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 198, &int_handler_198, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 199, &int_handler_199, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 200, &int_handler_200, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 201, &int_handler_201, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 202, &int_handler_202, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 203, &int_handler_203, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 204, &int_handler_204, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 205, &int_handler_205, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 206, &int_handler_206, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 207, &int_handler_207, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 208, &int_handler_208, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 209, &int_handler_209, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 210, &int_handler_210, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 211, &int_handler_211, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 212, &int_handler_212, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 213, &int_handler_213, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 214, &int_handler_214, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 215, &int_handler_215, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 216, &int_handler_216, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 217, &int_handler_217, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 218, &int_handler_218, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 219, &int_handler_219, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 220, &int_handler_220, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 221, &int_handler_221, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 222, &int_handler_222, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 223, &int_handler_223, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 224, &int_handler_224, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 225, &int_handler_225, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 226, &int_handler_226, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 227, &int_handler_227, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 228, &int_handler_228, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 229, &int_handler_229, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 230, &int_handler_230, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 231, &int_handler_231, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 232, &int_handler_232, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 233, &int_handler_233, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 234, &int_handler_234, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 235, &int_handler_235, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 236, &int_handler_236, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 237, &int_handler_237, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 238, &int_handler_238, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 239, &int_handler_239, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 240, &int_handler_240, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 241, &int_handler_241, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 242, &int_handler_242, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 243, &int_handler_243, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 244, &int_handler_244, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 245, &int_handler_245, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 246, &int_handler_246, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 247, &int_handler_247, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 248, &int_handler_248, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 249, &int_handler_249, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 250, &int_handler_250, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 251, &int_handler_251, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 252, &int_handler_252, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 253, &int_handler_253, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 254, &int_handler_254, 0, 0x10);
	init_idt_desc((GATE*)(*idtaddr) + 255, &int_handler_255, 0, 0x10);

	return SHARED_IDTR;
}

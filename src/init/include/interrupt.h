#ifndef KINIT_INTR
#define KINIT_INTR 1

#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>
#include    <klib_ad/x86/interrupt.h>

EXTERN_C

//APIC Interrupts
//#define INT_VEC_APIC_CMCI	INTERNEL_INTERRUPT_BASE + 32	

#define INT_VEC_APIC_SPUR	39	//spurious	IRQ7
#define INT_VEC_APIC_TM	INTERNEL_INTERRUPT_BASE + 34
#define INT_VEC_APIC_PC	INTERNEL_INTERRUPT_BASE + 35
#define INT_VEC_APIC_LINT0	INTERNEL_INTERRUPT_BASE + 36
#define INT_VEC_APIC_LINT1	INTERNEL_INTERRUPT_BASE + 37
#define INT_VEC_APIC_ERR	INTERNEL_INTERRUPT_BASE + 38

#define INT_VEC_IOAPIC_IRQ0 INTERNEL_INTERRUPT_BASE + 39
#define INT_VEC_IOAPIC_IRQ1 INTERNEL_INTERRUPT_BASE + 40

#define APIC_TIMER_FREQUENCY    1000    //number of ticks per second

int interrupt(void* esp, uint32_t int_id);

void mask_interrupt(uint32_t int_id);
void unmask_interrupt(uint32_t int_id);

//Customizable Interrupt Handlers
typedef int (*interrupt_handler)(void*, uint32_t);  //(void* esp, uint32_t int_id)
//return 1 for failure //return 0 to iretd
//if nullptr is specified, a 1 will be returned
void set_interrupt_handler(interrupt_handler handler, uint32_t int_id);
interrupt_handler get_interrupt_handler(uint32_t int_id);
extern byte int_masks[256];

int c_idt_init();

// asm interrupt handlers
void int_handler_0();
void int_handler_1();
void int_handler_2();
void int_handler_3();
void int_handler_4();
void int_handler_5();
void int_handler_6();
void int_handler_7();
void int_handler_8();
void int_handler_9();
void int_handler_10();
void int_handler_11();
void int_handler_12();
void int_handler_13();
void int_handler_14();
void int_handler_15();
void int_handler_16();
void int_handler_17();
void int_handler_18();
void int_handler_19();
void int_handler_20();
void int_handler_21();
void int_handler_22();
void int_handler_23();
void int_handler_24();
void int_handler_25();
void int_handler_26();
void int_handler_27();
void int_handler_28();
void int_handler_29();
void int_handler_30();
void int_handler_31();
void int_handler_32();
void int_handler_33();
void int_handler_34();
void int_handler_35();
void int_handler_36();
void int_handler_37();
void int_handler_38();
void int_handler_39();
void int_handler_40();
void int_handler_41();
void int_handler_42();
void int_handler_43();
void int_handler_44();
void int_handler_45();
void int_handler_46();
void int_handler_47();
void int_handler_48();
void int_handler_49();
void int_handler_50();
void int_handler_51();
void int_handler_52();
void int_handler_53();
void int_handler_54();
void int_handler_55();
void int_handler_56();
void int_handler_57();
void int_handler_58();
void int_handler_59();
void int_handler_60();
void int_handler_61();
void int_handler_62();
void int_handler_63();
void int_handler_64();
void int_handler_65();
void int_handler_66();
void int_handler_67();
void int_handler_68();
void int_handler_69();
void int_handler_70();
void int_handler_71();
void int_handler_72();
void int_handler_73();
void int_handler_74();
void int_handler_75();
void int_handler_76();
void int_handler_77();
void int_handler_78();
void int_handler_79();
void int_handler_80();
void int_handler_81();
void int_handler_82();
void int_handler_83();
void int_handler_84();
void int_handler_85();
void int_handler_86();
void int_handler_87();
void int_handler_88();
void int_handler_89();
void int_handler_90();
void int_handler_91();
void int_handler_92();
void int_handler_93();
void int_handler_94();
void int_handler_95();
void int_handler_96();
void int_handler_97();
void int_handler_98();
void int_handler_99();
void int_handler_100();
void int_handler_101();
void int_handler_102();
void int_handler_103();
void int_handler_104();
void int_handler_105();
void int_handler_106();
void int_handler_107();
void int_handler_108();
void int_handler_109();
void int_handler_110();
void int_handler_111();
void int_handler_112();
void int_handler_113();
void int_handler_114();
void int_handler_115();
void int_handler_116();
void int_handler_117();
void int_handler_118();
void int_handler_119();
void int_handler_120();
void int_handler_121();
void int_handler_122();
void int_handler_123();
void int_handler_124();
void int_handler_125();
void int_handler_126();
void int_handler_127();
void int_handler_128();
void int_handler_129();
void int_handler_130();
void int_handler_131();
void int_handler_132();
void int_handler_133();
void int_handler_134();
void int_handler_135();
void int_handler_136();
void int_handler_137();
void int_handler_138();
void int_handler_139();
void int_handler_140();
void int_handler_141();
void int_handler_142();
void int_handler_143();
void int_handler_144();
void int_handler_145();
void int_handler_146();
void int_handler_147();
void int_handler_148();
void int_handler_149();
void int_handler_150();
void int_handler_151();
void int_handler_152();
void int_handler_153();
void int_handler_154();
void int_handler_155();
void int_handler_156();
void int_handler_157();
void int_handler_158();
void int_handler_159();
void int_handler_160();
void int_handler_161();
void int_handler_162();
void int_handler_163();
void int_handler_164();
void int_handler_165();
void int_handler_166();
void int_handler_167();
void int_handler_168();
void int_handler_169();
void int_handler_170();
void int_handler_171();
void int_handler_172();
void int_handler_173();
void int_handler_174();
void int_handler_175();
void int_handler_176();
void int_handler_177();
void int_handler_178();
void int_handler_179();
void int_handler_180();
void int_handler_181();
void int_handler_182();
void int_handler_183();
void int_handler_184();
void int_handler_185();
void int_handler_186();
void int_handler_187();
void int_handler_188();
void int_handler_189();
void int_handler_190();
void int_handler_191();
void int_handler_192();
void int_handler_193();
void int_handler_194();
void int_handler_195();
void int_handler_196();
void int_handler_197();
void int_handler_198();
void int_handler_199();
void int_handler_200();
void int_handler_201();
void int_handler_202();
void int_handler_203();
void int_handler_204();
void int_handler_205();
void int_handler_206();
void int_handler_207();
void int_handler_208();
void int_handler_209();
void int_handler_210();
void int_handler_211();
void int_handler_212();
void int_handler_213();
void int_handler_214();
void int_handler_215();
void int_handler_216();
void int_handler_217();
void int_handler_218();
void int_handler_219();
void int_handler_220();
void int_handler_221();
void int_handler_222();
void int_handler_223();
void int_handler_224();
void int_handler_225();
void int_handler_226();
void int_handler_227();
void int_handler_228();
void int_handler_229();
void int_handler_230();
void int_handler_231();
void int_handler_232();
void int_handler_233();
void int_handler_234();
void int_handler_235();
void int_handler_236();
void int_handler_237();
void int_handler_238();
void int_handler_239();
void int_handler_240();
void int_handler_241();
void int_handler_242();
void int_handler_243();
void int_handler_244();
void int_handler_245();
void int_handler_246();
void int_handler_247();
void int_handler_248();
void int_handler_249();
void int_handler_250();
void int_handler_251();
void int_handler_252();
void int_handler_253();
void int_handler_254();
void int_handler_255();

EXTERN_C_END

#endif

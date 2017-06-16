// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_INSTRUCTION_H_
#define _KLIB_INSTRUCTION_H_

#include <klib_sl/type.h>

/* Port IO */
void outb(uint16_t port, uint8_t val);
#ifndef out_byte
#define out_byte outb
#endif
void outw(uint16_t port, uint16_t val);
#ifndef out_word
#define out_word outw
#endif
void outd(uint16_t port, uint32_t val);
#ifndef out_dword
#define out_dword outd
#endif

uint8_t inb(uint16_t port);
#ifndef in_byte
#define in_byte inb
#endif
uint16_t inw(uint16_t port);
#ifndef in_word
#define in_word inw
#endif
uint32_t ind(uint16_t port);
#ifndef in_dword
#define in_dword ind
#endif

/* Control Registers' Access */
uintreg_t read_cr0(void);
void write_cr0(uintreg_t val);
uintreg_t read_cr1(void);
void write_cr1(uintreg_t val);
uintreg_t read_cr2(void);
void write_cr2(uintreg_t val);
uintreg_t read_cr3(void);
void write_cr3(uintreg_t val);
uintreg_t read_cr4(void);
void write_cr4(uintreg_t val);

/* Model Specific Register Access */
void wrmsr(uint32_t msr_id, uint64_t msr_value);
uint64_t rdmsr(uint32_t msr_id);
void readmsr(uint32_t msr, byte* b_array_8);
void writemsr(uint32_t msr, byte* b_array_8);

/* Maskable Interrupt Control */
#define cli() __asm__ volatile ("cli")
#define sti() __asm__ volatile ("sti")

#endif

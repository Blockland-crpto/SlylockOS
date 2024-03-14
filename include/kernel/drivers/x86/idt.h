#ifndef __DRIVERS_X86_IDT_H
#define __DRIVERS_X86_IDT_H

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

void idt_install();

#endif
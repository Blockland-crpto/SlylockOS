#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

struct regs {
	unsigned int gs, fs, es, ds;      /* pushed the segs last */
	unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
	unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
	unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

/** INTERRUPT DESCRIPTOR TABLE START **/
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();
/** INTERRUPT DESCRIPTOR TABLE END **/

/** NON MASKABLE INTERRUPT START **/
void nmi_enable();
void nmi_disable();
/** NON MASKABLE INTERRUPT END **/

/** INTERRUPT SERVICE ROUTINES START **/
void isr_install();
/** INTERRUPT SERVICE ROUTINES END **/

/** INTERRUPT REQUEST START **/
void irq_install();
void irq_install_handler();
void irq_uninstall_handler();
/** INTERRUPT REQUEST END **/
#endif
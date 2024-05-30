#ifndef __KERNEL_IDT_H
#define __KERNEL_IDT_H

#if defined(__cplusplus)
extern "C" {
#endif
	void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

	void idt_install();


#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
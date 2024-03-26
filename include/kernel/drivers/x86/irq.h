#ifndef __DRIVERS_X86_IRQ_H
#define __DRIVERS_X86_IRQ_H

#if defined(__cplusplus)
extern "C" {
#endif
	void irq_install();
	void irq_install_handler();
	void irq_uninstall_handler();

#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif
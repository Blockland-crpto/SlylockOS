#include <drivers/cpu/nmi.h>
#include <system/mod.h>
 

void nmi_init() {
	module_t modules_nmi_nmi = MODULE("kernel.modules.nmi.nmi", "provides a handler for non maskable interrupts (CORE)");
	nmi_enable();
	INIT(modules_nmi_nmi);
	 
}
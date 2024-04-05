#include <drivers/nmi.h>
#include <system/modules.h>
#include <libssp.h>

void nmi_init() {
	module_t modules_nmi = MODULE("kernel.modules.nmi", "provides a handler for non maskable interrupts (CORE)");
	INIT(modules_nmi);
	nmi_enable();
	DONE(modules_nmi);
	 
}
#include <drivers/cpu/nmi.h>
#include <system/mod.h>
#include <system/task.h>

void nmi_init() {
	create_task("nmi_initalizer", TASK_PRIORITY_KERNEL, TASK_ID_KERNEL);
	module_t modules_nmi_nmi = MODULE("kernel.modules.nmi.nmi", "provides a handler for non maskable interrupts (CORE)");
	nmi_enable();
	INIT(modules_nmi_nmi);
	modify_task(TASK_STATE_ENDED);
}
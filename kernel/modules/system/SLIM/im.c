#include <system/im.h>
#include <slibaries/shell.h>
#include <slibaries/gui.h>
#include <system/mod.h>
#include <system/task.h>


void im_init() {
	create_task("im_initalizer", TASK_PRIORITY_KERNEL, TASK_ID_KERNEL);
	module_t modules_im_im = MODULE("kernel.modules.im.im", "the interaction manager for the kernel (CORE)");
	INIT(modules_im_im);
	modify_task(TASK_STATE_ENDED);
}
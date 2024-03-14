#include <system/im.h>
#include <slibaries/shell.h>
#include <libtui.h>
#include <system/mod.h>
 


void im_init() {
	
	module_t modules_im_im = MODULE("kernel.modules.im.im", "the interaction manager for the kernel (CORE)");
	INIT(modules_im_im);
}
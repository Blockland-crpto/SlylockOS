#include <system/modules.h>
#include <shell/shell.h>
#include <libssp.h>


#define NULL ((char *)0)

int cf = 1;
int dfs = 1;
void shell_init(){
	module_t modules_shell_shell = MODULE("kernel.modules.shell.shell", "User interface for the kernel (CORE)");


	char** deps;
	deps[0] = "kernel.modules.timer.timer";
	deps[1] = "kernel.modules.im.im";
	DEPS(modules_shell_shell, deps);
	INIT(modules_shell_shell);
}

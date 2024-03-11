#include <system/mod.h>
#include <slibaries/shell.h>
#include <drivers/perip/timer.h>
#include <drivers/io/ports.h>
#include <string.h>
#include <drivers/fs/fs.h>
#include <system/debug.h>
#include <drivers/vga.h>
#include <slibaries/gui.h>
#include <system/kernel.h>
#include <drivers/perip/keybrd.h>

#define NULL ((char *)0)

int cf = 1;
int dfs = 1;
void shell_init(){
	module_t modules_shell_shell = MODULE("kernel.modules.shell.shell", "User interface for the kernel (CORE)");

	
	themeindex = 3;

	loadingscreen("Starting Up", "MiniOS is starting...");
	login_screen();
	tui_shell();

	char** deps;
	deps[0] = "kernel.modules.timer.timer";
	deps[1] = "kernel.modules.im.im";
	DEPS(modules_shell_shell, deps);
	INIT(modules_shell_shell);
}

void login_screen() {
	make_gui(themeindex, themeindex, 0, 2);
	putstrpos("Welcome to MiniOS!", 30, 12, COLOR_BLU, COLOR_WHT, 30);
	time_sleep(7000000);
}

void tui_shell() {
	make_gui(themeindex, themeindex, 0, 2);
	userinputmode = SHELL_APP_ID;
}

void clear_scr(){
  clear(COLOR_WHT, COLOR_BLK);
  set_cursor_pos(0,0);
}
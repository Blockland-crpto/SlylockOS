#include <slibaries/shell.h>
#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>
#include <drivers/vga.h>
#include <system/debug.h>
#include <system/im.h>
#include <string.h>
#include <system/kernel.h>


void cmd_init() {
	shellinput = 1;
	make_gui(themeindex, themeindex, 1, 2);
	make_gui_windows("Cmd:", "", 4, 3, 70, 20);
	for (int x = 5; x < 70; x++) {
		for (int y = 5; y < 20; y++) {
			putpos('#', COLOR_BLK, COLOR_BLK, x, y);
		}
	}

	set_cursor_pos(5, 5);
}

void cmd(char* str[]) {

	if (strcmp(str, "about") == 0) {
		set_cursor_pos(5, 6);
		kprintf("About MINI");
		set_cursor_pos(5, 7);
		kprintf("Kernel Version: V1.0.0");
		set_cursor_pos(5, 8);
		kprintf("SLIM Version: V1.0.0");
		set_cursor_pos(5, 9);
		kprintf("AppToolkit Version: V1.0.0");
		set_cursor_pos(5, 10);
		kprintf("Press enter to return");
		userinputmode = CMD_APP_ID;
	} else if (strcmp(str, "exit") == 0) {
		tui_reset();
	} else if (strcmp(str, "shutdown") == 0) {
		shutdown();
	} else if (strcmp(str, "reboot") == 0) {
		reboot();
	} else if (strcmp(str, "help") == 0) {
		set_cursor_pos(5, 6);
		kprintf("MINI Shell Commands");
		set_cursor_pos(5, 7);
		kprintf("about - Displays information about the OS");
		set_cursor_pos(5, 8);
		kprintf("exit - Exits the shell");
		set_cursor_pos(5, 9);
		kprintf("shutdown - Shuts down the OS");
		set_cursor_pos(5, 10);
		kprintf("reboot - Reboots the OS");
		set_cursor_pos(5, 11);
		kprintf("help - Displays this message");
		set_cursor_pos(5, 12);
		kprintf("resetvga - resets the display system");
		set_cursor_pos(5, 13);
		kprintf("Press enter to return");
		userinputmode = CMD_APP_ID;
	} else if (strcmp(str, "resetvga") == 0) {
		clear_scr();
		cmd_init();
	}
	shellinput = 0;
}
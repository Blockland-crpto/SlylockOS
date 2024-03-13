#include <drivers/vga.h>
#include <system/debug.h>
#include <system/task.h>


void panic(char* reason, int errno) {
	task_t current = taskpool[running_tasks];
	char* buf;
	color_screen(3, 3);
	putstr("KERNEL PANIC HAS OCCURED.\n", COLOR_WHT, COLOR_GRN);
	putstr("ERROR CODE: 0x", COLOR_LBU, COLOR_GRN);
	putstr(itoa(errno, buf, 10), COLOR_LBU, COLOR_GRN);
	putstr("\nREASON: ", COLOR_WHT, COLOR_GRN);
	putstr(reason, COLOR_LBU, COLOR_GRN);
	putstr("\nProcess Name: ", COLOR_WHT, COLOR_GRN);
	putstr(current.name, COLOR_LBU, COLOR_GRN);
	putstr(" Was being run at this time", COLOR_WHT, COLOR_GRN);
	while(1);
}
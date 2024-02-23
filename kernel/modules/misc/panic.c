#include <screen.h>


void panic(char* reason, int errno) {
	char* buf;
	color_screen(3, 3);
	putstr("KERNEL PANIC HAS OCCURED.\n", COLOR_WHT, COLOR_GRN);
	putstr("ERROR CODE: 0x", COLOR_LBU, COLOR_GRN);
	putstr(itoa(errno, buf, 10), COLOR_LBU, COLOR_GRN);
	putstr("\nREASON: ", COLOR_WHT, COLOR_GRN);
	putstr(reason, COLOR_LBU, COLOR_GRN);
	while(1);
}

void warn(char* reason) {
	putstr("WARN: ", COLOR_RED, COLOR_BLK);
	putstr(reason, COLOR_WHT, COLOR_BLK);
	putstr("\n", COLOR_WHT, COLOR_BLK);
}
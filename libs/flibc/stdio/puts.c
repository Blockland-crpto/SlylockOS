#include <stdio.h>
#include <drivers/vga.h>

int puts(const char* s) {
	putstr(s, COLOR_WHT, COLOR_BLK);
	return 0;
}
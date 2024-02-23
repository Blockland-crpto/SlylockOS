#include <screen.h>

void kprintc(const char *ch) {
	putchar(ch, COLOR_WHT, COLOR_BLK); // Print 1 character, but white
} 
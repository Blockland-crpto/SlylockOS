#include <libvga.h>
#include <libssp.h>

void kprintc(const char *ch) {
	kputchar(ch, COLOR_WHT, COLOR_BLK); // Print 1 character, but white
} 
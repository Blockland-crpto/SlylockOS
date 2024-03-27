#include <libvga.h>
#include <libssp.h>

void kprintf(const char *string){
	while(*string != '\0'){ // Print string, but white
		kputchar(*string++, COLOR_WHT, COLOR_BLK);
	}
}

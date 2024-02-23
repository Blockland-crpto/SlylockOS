#include <screen.h>

void kprintf(const char *string){
	while(*string != '\0'){ // Print string, but white
		putchar(*string++, COLOR_WHT, COLOR_BLK);
	}
}

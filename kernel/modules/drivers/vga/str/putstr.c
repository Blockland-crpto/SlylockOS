#include <drivers/vga.h>

void putstr(const char *string, const unsigned char fg_color, const unsigned char bg_color){
	while (*string != '\0'){ // Get each character of the string until the \0 character and print it
		putchar(*string++, fg_color, bg_color);
	}
}
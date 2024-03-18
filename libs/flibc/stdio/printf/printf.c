#include <stdio.h>
#include <string.h>
#include <drivers/vga.h>
#include <stdarg.h>

int printf(const char *format, ...) {
	va_list ap;
	va_start(ap, format);

	char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			char* buf;
			switch (*ptr++) {
				case 's':
					kprintf(va_arg(ap, char *));
					break;
				case 'd':
					kprintf(itoa(va_arg(ap, char *), buf, 10));
					break;
				case 'x':
					kprintf(itoa(va_arg(ap, char *), buf, 16));
					break;
				default:
					return -1;
			}
		} else {
			kprintc(*ptr++);
			len++;
		}
	}

	va_end(ap);
	return len-1;
}
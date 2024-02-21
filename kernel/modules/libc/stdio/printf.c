#include <stdio.h>
#include <string.h>
#include <screen.h>
#include <stdarg.h>

void printf(char *format, ...) {
	va_list ap;
	va_start(ap, format);

	char *ptr = format;

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
			}
		} else {
			kprintc(*ptr++);
		}
	}

	va_end(ap);
}
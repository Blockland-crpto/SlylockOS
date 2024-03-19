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
			int num;
			char* str;
			char buf[256];
			switch (*ptr++) {
				case 's': {
					kprintf(va_arg(ap, const char *));
					break;
				} case 'd': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 10);
					kprintf(str);
					break;
				} case 'x': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 16);
					kprintf(str);
					break;
				} default: {
					return -1;
				}
			}
		} else {
			kprintc(*ptr++);
			len++;
		}
	}

	va_end(ap);
	return len;
}
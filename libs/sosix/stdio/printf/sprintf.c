#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <libssp.h>

int sprintf(char *restrict s, const char *restrict template, ...) {
	va_list ap;
	va_start(ap, template);

	char *ptr = template;
	int len = 0;
	while (*ptr) {
		if (*ptr == '%') {
			ptr++;
			int num;
			char* str;
			char buf[256];
			switch (*ptr++) {
				case 's': {
					str = va_arg(ap, const char *);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} case 'd': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 10);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} case 'x': {
					num = va_arg(ap, int);
					str = itoa(num, buf, 16);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} default: {
					return -1;
				}
			}
		} else {
			*s++ = *ptr++;
			len++;
		}
	}
	
	va_end(ap);
	return len;
}
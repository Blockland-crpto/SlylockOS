#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <libssp.h>

int sprintf(char *restrict s, const char *restrict template, ...) {
	va_list ap;
	va_start(ap, template);

	const char *ptr = template;
	int len = 0;
	while (*ptr) {
		if (*ptr == '%') {
			ptr++;
			char buf[256];
			switch (*ptr++) {
				case 's': {
					const char* str = va_arg(ap, const char *);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} case 'd': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 10);
					while (*str) {
						*s++ = *str++;
						len++;
					}
					break;
				} case 'x': {
					int num = va_arg(ap, int);
					const char* str = itoa(num, buf, 16);
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
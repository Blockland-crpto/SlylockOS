#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <libssp.h>
#include <libfs.h>


//REQUIRES REWRITE

int vdprintf(fs_node_t *fd, const char *format, va_list ap) {
	uint8_t *fbuf = (uint8_t*)malloc(fd->length);
	uint32_t startsize = read_fs(fd, 0, fd->length, fbuf);
	const char *ptr = format;
	int len = 0;
	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			char buf[256];
			switch (*ptr++) {
				case 's':
					write_fs(fd, startsize, fd->length, (uint8_t*)va_arg(ap, char *));
					break;
				case 'd':
					write_fs(fd, startsize, fd->length, (uint8_t*)itoa(va_arg(ap, int), buf, 10));
					break;
				case 'x':
					write_fs(fd, startsize, fd->length, (uint8_t*)itoa(va_arg(ap, int), buf, 16));
					break;
				default:
					return -1;
			}
		} else {
			//FIXME: compiler does not like casting to 
			//smaller types
			write_fs(fd, startsize, fd->length, (uint8_t*)*ptr++);
			len++;
		}
	}

	va_end(ap);
	return len-1;
}

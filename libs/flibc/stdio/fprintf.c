#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <drivers/fs/fs.h>


int fprintf(FILE* stream, const char *format, ...) {
	uint8_t *fbuf = (uint8_t*)malloc(stream->node->length);
	uint32_t startsize = read_fs(stream->node, 0, stream->node->length, fbuf);
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
					write_fs(stream->node, startsize, stream->node->length, (uint8_t*)va_arg(ap, char *));
					break;
				case 'd':
					write_fs(stream->node, startsize, stream->node->length, (uint8_t*)itoa(va_arg(ap, char *), buf, 10));
					break;
				case 'x':
					write_fs(stream->node, startsize, stream->node->length, (uint8_t*)itoa(va_arg(ap, char *), buf, 16));
					break;
				default:
					return -1;
			}
		} else {
			write_fs(stream->node, startsize, stream->node->length, (uint8_t*)*ptr++);
			len++;
		}
	}

	va_end(ap);
	return len-1;
}
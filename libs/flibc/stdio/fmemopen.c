#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

/*
FILE *fmemopen(void *restrict buf, size_t size, const char *restrict mode) {
	FILE *file;
	file->name = "Membuf";
	file->mode = mode;
	file->stream = (uint8_t*)buf;
}
*/
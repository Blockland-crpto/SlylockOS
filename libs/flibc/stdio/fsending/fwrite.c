#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include <drivers/fs/fs.h>

size_t fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream) {
	size_t total_elements_written = 0;
	const uint8_t *byte_ptr = (const uint8_t *)ptr; // Treat ptr as an array of bytes

	for (size_t i = 0; i < nitems; i++) {
		for (size_t j = 0; j < size; j++) {
			fputc(byte_ptr[i * size + j], stream); // Write a byte
		}
		total_elements_written++;
	}

	return total_elements_written;
}
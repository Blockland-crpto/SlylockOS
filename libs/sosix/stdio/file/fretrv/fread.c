#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

size_t fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream) {
	size_t total_elements_read = 0;
	for (size_t i = 0; i < nitems; i++) {
		for (size_t j = 0; j < size; j++) {
			int byte = fgetc(stream); // Read a byte
			if (byte == EOF) {
				// Return if end of file or error
				return total_elements_read;
			}
			// Store the byte in the correct position in the buffer
			*((char *)ptr + i * size + j) = (char)byte;
		}
		total_elements_read++;
	}
	return total_elements_read;
}

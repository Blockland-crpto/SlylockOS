#include <string.h>
#include <stddef.h>
#include <libmem.h>
#include <libssp.h>

#define DICT_LEN 256

int *create_delim_dict(int *delim) {
	int *d = (int*)kalloc(sizeof(int)*DICT_LEN);
	memset((void*)d, 0, sizeof(int)*DICT_LEN);

	for	(int i = 0; i < strlen((const char*)delim); i++) {
		d[delim[i]] = 1;
	}
	return d;
}
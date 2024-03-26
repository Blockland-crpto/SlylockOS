#include <string.h>
#include <stddef.h>
#include <system/memory.h>
#include <libssp.h>

#define DICT_LEN 256

int *create_delim_dict(char *delim)
{
	int *d = (int*)kalloc(sizeof(int)*DICT_LEN);
	memset((void*)d, 0, sizeof(int)*DICT_LEN);

	int i;
	for(i=0; i< strlen(delim); i++) {
		d[delim[i]] = 1;
	}
	return d;
}
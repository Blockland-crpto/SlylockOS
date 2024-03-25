#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>

int atoi(const char* str) {
	return (int) strtol(str, (char**) NULL, 10);
}
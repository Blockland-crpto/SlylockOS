#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>

double atof(const char *str) {
	return strtod(str, (char**)NULL);
}
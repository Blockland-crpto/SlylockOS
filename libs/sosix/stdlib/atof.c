#include <stdlib.h>
#include <stddef.h>

double atof(const char *str) {
	return strtod(str, (char**)NULL);
}
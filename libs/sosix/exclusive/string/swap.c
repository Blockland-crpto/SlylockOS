#include <string.h>
#include <libssp.h>

void swap(char *x, char *y) {
	char t = *x; *x = *y; *y = t;
}
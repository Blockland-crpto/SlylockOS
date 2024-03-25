#include <ctype.h>
#include <libssp.h>

int isdigit(char c) {
	if (c>='0' && c<='9') return 1;
	return 0;
}
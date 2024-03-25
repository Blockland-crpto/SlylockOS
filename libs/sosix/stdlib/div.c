//Copied of the GNU C LIB
#include <stdlib.h>
#include <libssp.h>

div_t div(int nume, int denom) {
	div_t result;
	result.quot = nume / denom;
	result.rem = nume % denom;
	return result;
}
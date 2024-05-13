#include <stdlib.h>
#include <libssp.h>

// From https://stackoverflow.com/a/4768189

static unsigned long int next = 1;

int rand(void) { // RAND_MAX assumed to be the max int number
	next = next * 1103515245 + 12345;
	return (unsigned int)(next/65536) % 4294967295;
}

void srand(unsigned int seed) {
	next = seed;
}
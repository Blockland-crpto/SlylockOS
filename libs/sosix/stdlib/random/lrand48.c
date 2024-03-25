#include <stdlib.h>

long lrand48(void) {
	const unsigned long long a = 0x5DEECE66DULL;
	const unsigned long long c = 0xBULL;
	const unsigned long long m = (1ULL << 48);

	unsigned long long next = _rand48_seed[0] * a + c;
	_rand48_seed[0] = (unsigned short)(next & 0xFFFF);
	next >>= 16;
	next += _rand48_seed[1] * a + c;
	_rand48_seed[1] = (unsigned short)(next & 0xFFFF);
	next >>= 16;
	next += _rand48_seed[2] * a + c;
	_rand48_seed[2] = (unsigned short)(next & 0xFFFF);

	return (long)(next >> 16) & 0x7FFFFFFF;
}
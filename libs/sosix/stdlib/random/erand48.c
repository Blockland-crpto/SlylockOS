#include <stdlib.h>


double erand48(unsigned short xsubi[3]) {
	const unsigned long long a = 0x5DEECE66DULL;
	const unsigned long long c = 0xBULL;
	const unsigned long long m = (1ULL << 48);

	unsigned long long next = xsubi[0] * a + c;
	xsubi[0] = (unsigned short)(next & 0xFFFF);
	next >>= 16;
	next += xsubi[1] * a + c;
	xsubi[1] = (unsigned short)(next & 0xFFFF);
	next >>= 16;
	next += xsubi[2] * a + c;
	xsubi[2] = (unsigned short)(next & 0xFFFF);

	double result = next / (double)m;
	return result;
}
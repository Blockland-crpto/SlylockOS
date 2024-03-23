#include <stdlib.h>

int atoi(char* str)
{
	// Initialize result
	int res = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		res = res * 10 + str[i] - '0';

	// return result.
	return res;
}
#include <string.h>
#include <stddef.h>

// Function to implement `strstr()` function
const char* strstr(const char* X, const char* Y)
{
	while (*X != '\0')
	{
		if ((*X == *Y) && compare(X, Y)) {
			return X;
		}
		X++;
	}

	return NULL;
}
#include <string.h>

int strspn (const char *s, const char *accept)
{
	const char *p;
	const char *a;
	int count = 0;

	for (p = s; *p != '\0'; ++p)
	{
		for (a = accept; *a != '\0'; ++a)
			if (*p == *a)
				break;
		if (*a == '\0')
			return count;
		else
			++count;
	}
	return count;
}
#include <string.h>

int memcmp(const void *s1, const void *s2, int len) {
	unsigned char *p = s1;
	unsigned char *q = s2;
	int charCompareStatus = 0;
	if (s1 == s2)
	{
		return charCompareStatus;
	}
	while (len > 0)
	{
		if (*p != *q) {
			charCompareStatus = (*p >*q)?1:-1;
			break;
		}
		len--;
		p++;
		q++;
	}
	return charCompareStatus;
}
#include <string.h>
#include <stdlib.h>
 

char *rstrstr(const char *str, const char *sub) {
	char *result;
	int i, j;
	int sub_len = strlen(sub);
	int found = 0;

	for (i = 0; str[i] != '\0'; i++) {
		if (strstr(&str[i], sub) == &str[i]) {
			found = 1;
			i += sub_len - 1;
		}
	}

	if (!found) {
		// No occurrence of sub in str
		return strdup(str);
	}

	result = (char *)malloc(strlen(str) + 1);
	i = j = 0;
	while (str[i] != '\0') {
		if (strstr(&str[i], sub) == &str[i]) {
			i += sub_len;
		} else {
			result[j++] = str[i++];
		}
	}
	result[j] = '\0';

	return result;
}
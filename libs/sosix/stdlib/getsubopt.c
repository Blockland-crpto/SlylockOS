#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <libssp.h>

int getsubopt(char **optionp, char * const *keylistp, char **valuep) {
	char *option = *optionp;
	char *key, *value;
	int i;

	// Skip leading whitespace
	while (*option && *option == ' ')
		option++;

	// Find the key
	key = option;
	while (*option && *option != '=' && *option != ' ')
		option++;

	// Find the value, if any
	if (*option == '=') {
		*option++ = '\0'; // Null terminate the key
		value = option;
		while (*option && *option != ' ')
			option++;
		if (*option)
			*option++ = '\0'; // Null terminate the value
	} else {
		value = NULL;
	}

	// Find the key in the keylist
	for (i = 0; keylistp[i]; i++) {
		if (strcmp(keylistp[i], key) == 0) {
			*optionp = option; // Update the option pointer
			*valuep = value;   // Set the value pointer
			return i;          // Return the key index
		}
	}

	return -1; // Key not found
}
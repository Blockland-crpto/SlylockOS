#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

void flockfile(FILE *file) {
	if (file != NULL) {
		if (!file->locked) {
			file->locked = true;
		}
	}
}
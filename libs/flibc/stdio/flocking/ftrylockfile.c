#include <stdio.h>
#include <stdbool.h>


int ftrylockfile(FILE *file) {
	if (!file->locked) {
		file->locked = true;
		return 0;
	} else {
		return 1;
	}
}
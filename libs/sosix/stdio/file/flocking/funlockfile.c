#include <stdio.h>
#include <stdbool.h>

void funlockfile(FILE *file) {
	file->locked = false;
}
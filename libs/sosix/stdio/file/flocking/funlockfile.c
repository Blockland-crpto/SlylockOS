#include <stdio.h>
#include <stdbool.h>
#include <libssp.h>

void funlockfile(FILE *file) {
	file->locked = false;
}
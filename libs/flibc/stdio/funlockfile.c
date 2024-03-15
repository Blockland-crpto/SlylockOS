#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <drivers/fs/fs.h>


void funlockfile(FILE *file) {
	file->locked = false;
	return;
}
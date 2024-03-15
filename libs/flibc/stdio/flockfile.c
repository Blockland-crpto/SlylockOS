#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <drivers/fs/fs.h>


void flockfile(FILE *file) {
	file->locked = true;
	return;
}
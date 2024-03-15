#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <drivers/fs/fs.h>


int ftrylockfile(FILE *file) {
	if (file->locked == true) {
		return 1;
	} else {
		file->locked = true;
		return 0;
	}
}
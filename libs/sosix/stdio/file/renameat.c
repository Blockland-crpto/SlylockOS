#include <stdio.h>
#include <libfs.h>
#include <string.h>
#include <libssp.h>

int renameat(fs_node_t* oldfd, const char *newName) {
	strcpy(oldfd->name, newName);
	return 0;
}
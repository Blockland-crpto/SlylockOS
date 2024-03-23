#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tempnam(const char *dir, const char *prefix) {
	char *str;
	char *directory = (char*)malloc(strlen(dir) + 1);
	if (dir == NULL) {
		str = P_tmpdir;
	}
	fs_node_t *exists = finddir_fs(fs_root, dir);
	if (exists == 0) {
		str = P_tmpdir;
	}
	strcat(str, "/");
	strcat(str, prefix);
	strcpy(directory, dir);
	return directory;
}
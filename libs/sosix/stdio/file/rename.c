#include <stdio.h>
#include <drivers/fs/fs.h>

int rename(const char *old, const char *newName) {
	fs_node_t *oldNode = finddir_fs(fs_root, old);
	if(oldNode == NULL) {
		return EOF;
	}
	rename_file_fs(oldNode, newName);
	return 0;
}
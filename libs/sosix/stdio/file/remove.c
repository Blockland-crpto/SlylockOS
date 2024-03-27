#include <stdio.h>
#include <libfs.h>
#include <libssp.h>

int remove (const char* path) {
	fs_node_t* file = finddir_fs(fs_root, path);
	if (file == NULL) {
		return -1;
	}
	delete_file_fs(file->name);
}
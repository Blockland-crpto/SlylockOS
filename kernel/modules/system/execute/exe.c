#include <system/exe.h>

#include <drivers/fs/fs.h>
#include <system/mem.h>

void execute_program(char* filename) {
	char buf[256];
	fs_node_t *fsnode = finddir_fs(fs_root, filename);
	uint32_t sz = read_fs(fsnode, 0, 256, buf);
	int j;
	char* to_execute = (char*) kalloc(256);
	char* heap = (char*) kalloc(128);
	run_external(buf, heap);
}	
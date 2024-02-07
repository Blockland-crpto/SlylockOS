#include <execute.h>

#include <fs.h>
#include <memory.h>

void execute_program(char* filename) {
	char buf[256];
	fs_node_t *fsnode = finddir_fs(fs_root, filename);
	uint32_t sz = read_fs(fsnode, 0, 256, buf);
	int j;
	char* to_execute = (char*) malloc(256);
	char* heap = (char*) malloc(128);
	run_external(buf, heap);

}	
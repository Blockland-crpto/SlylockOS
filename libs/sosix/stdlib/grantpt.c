#include <stdlib.h>
#include <drivers/fs/fs.h>

int grantpt(fs_node_t* node) {
	//the permissions flag is open to all by default
	node->gid = 0x0;
	node->uid = 0x1;
	return 0;
}
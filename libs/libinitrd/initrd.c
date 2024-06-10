/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
// initrd.c -- Defines the interface for and structures relating to the initial ramdisk.
#include <libmultiboot.h>
#include <libinitrd.h>
#include <libmem.h>
#include <stdint.h>
#include <stdbool.h>
#include <libmodule.h>
#include <string.h>
 
 


initrd_header_t *initrd_header;     // The header.
initrd_file_header_t *file_headers; // The list of file headers.
fs_node_t *initrd_dev;              // We also add a directory node for /dev, so we can mount devfs later on.
fs_node_t *root_nodes;              // List of file nodes.

struct dirent dirent; 

uint32_t initrd_create_file(char *name, uint8_t *buffer, uint32_t size) {
	uint32_t location = *((uint32_t*)mbi->mods_addr);
	if (nroot_nodes >= MAX_INITRD_FILES)
		return 0; // Maximum number of files reached

	// Create a new file header
	initrd_file_header_t new_header;
	strcpy(new_header.name, name);
	new_header.length = size;
	new_header.offset = new_header.length;
	memcpy((uint8_t *)(location + sizeof(initrd_header_t) + (nroot_nodes * sizeof(initrd_file_header_t))), &new_header, sizeof(initrd_file_header_t));

	// Copy the data from the buffer to the initrd
	memcpy((uint8_t *)(location + new_header.offset), buffer, size);

	// Update the initrd header
	initrd_header->nfiles++;

	// Update the file headers array
	file_headers = (initrd_file_header_t *)(location + sizeof(initrd_header_t));

	// Create a new file node
	strcpy(root_nodes[nroot_nodes].name, name);
	root_nodes[nroot_nodes].mask = root_nodes[nroot_nodes].uid = root_nodes[nroot_nodes].gid = 0;
	root_nodes[nroot_nodes].length = size;
	root_nodes[nroot_nodes].inode = nroot_nodes;
	root_nodes[nroot_nodes].flags = FS_FILE;
	root_nodes[nroot_nodes].read = &initrd_read;
	root_nodes[nroot_nodes].write = &initrd_write;
	root_nodes[nroot_nodes].rename = &initrd_rename_file;
	root_nodes[nroot_nodes].readdir = 0;
	root_nodes[nroot_nodes].finddir = 0;
	root_nodes[nroot_nodes].open = 0;
	root_nodes[nroot_nodes].close = 0;
	root_nodes[nroot_nodes].impl = 0;

	nroot_nodes++;

	return size;
}

uint32_t initrd_delete_file(char *name) {
	uint32_t location = *((uint32_t*)mbi->mods_addr);

	// Find the file header for the file to delete
	initrd_file_header_t* header = NULL;
	for (uint32_t i = 0; i < initrd_header->nfiles; i++) {
		initrd_file_header_t* current_header = (initrd_file_header_t*)(location + sizeof(initrd_header_t) + (i * sizeof(initrd_file_header_t)));
		if (strcmp(current_header->name, name) == 0) {
			header = current_header;
			break;
		}
	}

	if (header == NULL) {
		return 0; // File not found
	}

	// Update the initrd header
	initrd_header->nfiles--;

	// Shift the remaining file headers to remove the deleted file
	for (uint32_t i = 0; i < initrd_header->nfiles; i++) {
		initrd_file_header_t* current_header = (initrd_file_header_t*)(location + sizeof(initrd_header_t) + ((i + 1) * sizeof(initrd_file_header_t)));
		memcpy((uint8_t *)(location + sizeof(initrd_header_t) + (i * sizeof(initrd_file_header_t))), current_header, sizeof(initrd_file_header_t));
	}

	// Clear the last file header
	memset((uint8_t *)(location + sizeof(initrd_header_t) + (initrd_header->nfiles * sizeof(initrd_file_header_t))), 0, sizeof(initrd_file_header_t));

	// Update the file headers array
	file_headers = (initrd_file_header_t *)(location + sizeof(initrd_header_t));

	// Find and remove the file node
	for (int i = 0; i < nroot_nodes; i++) {
		if (strcmp(root_nodes[i].name, name) == 0) {
			// Shift the remaining file nodes to remove the deleted file
			for (int j = i; j < nroot_nodes - 1; j++) {
				root_nodes[j] = root_nodes[j + 1];
			}
			nroot_nodes--;
			break;
		}
	}

	return header->length;
}

uint32_t initrd_rename_file(fs_node_t *node, const char *name) {
	initrd_file_header_t header = file_headers[node->inode];
	strcpy(header.name, name);
	strcpy(node->name, name);
	return 0;
}

void initrd_create_dir(char *name) {
	uint32_t location = *((uint32_t*)mbi->mods_addr);
	struct dirent dirnode;
	strcpy(dirnode.name, name);
	initrd_header->nfiles++;

	memcpy((uint8_t *)(location + sizeof(dirnode) + (nroot_nodes * sizeof(initrd_file_header_t))), &dirnode, sizeof(dirnode));
	// Create a new file node
	strcpy(root_nodes[nroot_nodes].name, name);
	root_nodes[nroot_nodes].mask = root_nodes[nroot_nodes].uid = root_nodes[nroot_nodes].gid = 0;
	root_nodes[nroot_nodes].length = 0;
	root_nodes[nroot_nodes].inode = nroot_nodes;
	root_nodes[nroot_nodes].flags = FS_DIRECTORY;
	root_nodes[nroot_nodes].read = 0;
	root_nodes[nroot_nodes].write = 0;
	root_nodes[nroot_nodes].rename = &initrd_rename_dir;
	root_nodes[nroot_nodes].readdir = &initrd_readdir;
	root_nodes[nroot_nodes].finddir = &initrd_find;
	root_nodes[nroot_nodes].open = 0;
	root_nodes[nroot_nodes].close = 0;
	root_nodes[nroot_nodes].impl = 0;

	nroot_nodes++;

	return;
}

uint32_t initrd_delete_dir(char *name) {
	int i;
	for (i = 0; i < nroot_nodes; i++) {
		if (strcmp(root_nodes[i].name, name) == 0 && (root_nodes[i].flags & FS_DIRECTORY)) {
			// Remove the directory entry from root_nodes
			for (int j = i; j < nroot_nodes - 1; j++) {
				root_nodes[j] = root_nodes[j + 1];
			}
			nroot_nodes--;
			return 0; // Success
		}
	}
	return -1; // Directory not found
}

uint32_t initrd_rename_dir(fs_node_t *node, const char *name) {
	strcpy(node->name, name);
	return 0;
}

uint32_t initrd_write(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
	if (node->flags & FS_DIRECTORY)
		return 0; // Directories are read-only in this example

	initrd_file_header_t *header = &file_headers[node->inode];
	if (offset + size > header->length)
		size = header->length - offset;

	// Copy the data from the buffer to the initrd
	memcpy((uint8_t *)(header->offset) + offset, buffer, size);

	return size;
}

uint32_t initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer) {
   initrd_file_header_t header = file_headers[node->inode];
   if (offset > header.length)
       return 0;
   if (offset+size > header.length)
       size = header.length-offset;
   memcpy(buffer, (uint8_t*) (header.offset+offset), size);
   return size;
} 

struct dirent *initrd_readdir(fs_node_t *node, uint32_t index) {

	// lets first convert index into a int
	int iindex = (int)index;
	
   	if (node == initrd_root && index == 0) {
     	strcpy(dirent.name, "dev");
     	dirent.name[3] = 0; // Make sure the string is NULL-terminated.
     	dirent.ino = 0;
     	return &dirent;
   	}

   	if (iindex-1 >= nroot_nodes)
		return 0;
   	
	strcpy(dirent.name, root_nodes[index-1].name);
   	dirent.name[strlen(root_nodes[index-1].name)] = 0; // Make sure the string is NULL-terminated.
   	dirent.ino = root_nodes[index-1].inode;
   	return &dirent;
}

fs_node_t* initrd_find(const char *name) {
   	for (int i = 0; i < nroot_nodes; i++)
       	if (!strcmp(name, root_nodes[i].name))
           	return &root_nodes[i];
   	return 0;
} 

fs_node_t *initialise_initrd(uint32_t location) {
	module_t modules_initrd = MODULE("kernel.modules.initrd", "Provides initrd support for the kernel");
	INIT(modules_initrd);
   	
	// Initialise the main and file header pointers and populate the root directory.
   	initrd_header = (initrd_header_t *)location;
   	file_headers = (initrd_file_header_t *) (location+sizeof(initrd_header_t)); 
    
	// Initialise the root directory.
   	initrd_root = (fs_node_t*)kalloc(sizeof(fs_node_t));
   	strcpy(initrd_root->name, "initrd");
   	initrd_root->mask = initrd_root->uid = initrd_root->gid = initrd_root->inode = initrd_root->length = 0;
   	initrd_root->flags = FS_DIRECTORY;
   	initrd_root->read = 0;
   	initrd_root->write = 0;
   	initrd_root->open = 0;
   	initrd_root->close = 0;
   	initrd_root->readdir = &initrd_readdir;
   	initrd_root->finddir = &initrd_find;
   	initrd_root->ptr = 0;
   	initrd_root->impl = 0; 
   	
	// Initialise the /dev directory (required!)
   	initrd_dev = (fs_node_t*)kalloc(sizeof(fs_node_t));
   	strcpy(initrd_dev->name, "dev");
   	initrd_dev->mask = initrd_dev->uid = initrd_dev->gid = initrd_dev->inode = initrd_dev->length = 0;
   	initrd_dev->flags = FS_DIRECTORY;
   	initrd_dev->read = 0;
   	initrd_dev->write = 0;
   	initrd_dev->open = 0;
   	initrd_dev->close = 0;
   	initrd_dev->readdir = &initrd_readdir;
   	initrd_dev->finddir = &initrd_find;
   	initrd_dev->ptr = 0;
   	initrd_dev->impl = 0; 
   	root_nodes = (fs_node_t*)kalloc(sizeof(fs_node_t) * initrd_header->nfiles);
   	nroot_nodes = initrd_header->nfiles; 
   	
	// For every file...
   	for (uint32_t i = 0; i < initrd_header->nfiles; i++) {
       	// Edit the file's header - currently it holds the file offset
       	// relative to the start of the ramdisk. We want it relative to the start
       	// of memory.
       	file_headers[i].offset += location;
       	
		// Create a new file node.
       	strcpy(root_nodes[i].name, file_headers[i].name);
       	root_nodes[i].mask = root_nodes[i].uid = root_nodes[i].gid = 0;
       	root_nodes[i].length = file_headers[i].length;
       	root_nodes[i].inode = i;
       	root_nodes[i].flags = FS_FILE;
       	root_nodes[i].read = &initrd_read;
       	root_nodes[i].write = &initrd_write;
	   	root_nodes[i].rename = &initrd_rename_file;
       	root_nodes[i].readdir = 0;
       	root_nodes[i].finddir = 0;
       	root_nodes[i].open = 0;
       	root_nodes[i].close = 0;
       	root_nodes[i].impl = 0;
   	} 
   
    DONE(modules_initrd);
   	return initrd_root;
} 
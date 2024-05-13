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
/**
  \file      fs.h
  \brief     Filesystem support.
  \details   This header file is used for filesystem support.
  \author    matthyno
  \version   1.0.1
  \date      2021
  \copyright MIT License.
*/

#ifndef __LIBFS_H
#define __LIBFS_H

#include <system/types.h>

//patch to make the compiler shut up
struct fs_node;

/**
  \def FS_FILE
  \brief File flag for the filesystem

  Defines the file flag for the filesystem with hex 0x01
*/
#define FS_FILE        0x01
/**
  \def FS_DIRECTORY
  \brief Directory flag for the filesystem

  Defines the file flag for the filesystem with hex 0x02
*/
#define FS_DIRECTORY   0x02
/**
  \def FS_CHARDEVICE
  \brief Character device flag for the filesystem

  Defines the character device flag for the filesystem with hex 0x03
*/
#define FS_CHARDEVICE  0x03
/**
  \def FS_BLOCKDEVICE
  \brief Block device flag for the filesystem

  Defines the character device flag for the filesystem with hex 0x04
*/
#define FS_BLOCKDEVICE 0x04
/**
  \def FS_PIPE
  \brief Pipe flag for the filesystem

  Defines the pipe flag for the filesystem with hex 0x05
*/
#define FS_PIPE        0x05
/**
  \def FS_SYMLINK
  \brief Symbolic link flag for the filesystem

  Defines the symbolic link flag for the filesystem with hex 0x06
*/
#define FS_SYMLINK     0x06
/**
  \def FS_MOUNTPOINT
  \brief Mountpoint definition for the filesystem

  Defines the mountpoint flag for the filesystem with hex 0x08
*/
#define FS_MOUNTPOINT  0x08

#if defined(__cplusplus)
extern "C" {
#endif
	/**
	  \typedef uint32_t (*rename_type_t)(struct fs_node*,char*)
	  \brief This is equal to read_type_t.
	*/
	typedef uint32_t (*rename_type_t)(struct fs_node*,char*);

	/**
	  \typedef uint32_t (*read_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*)
	  \brief This is equal to write_type_t.
	*/
	typedef uint32_t (*read_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);

	/**
	  \typedef uint32_t (*write_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*)
	  \brief This is equal to read_type_t.
	*/
	typedef uint32_t (*write_type_t)(struct fs_node*,uint32_t,uint32_t,uint8_t*);

	/**
	  \typedef void (*open_type_t)(struct fs_node*)
	  \brief This is equal to close_type_t.
	*/
	typedef void (*open_type_t)(struct fs_node*);

	/**
	  \typedef void (*close_type_t)(struct fs_node*)
	  \brief This is equal to open_type_t.
	*/
	typedef void (*close_type_t)(struct fs_node*);


	typedef struct dirent * (*readdir_type_t)(struct fs_node*,uint32_t);

	typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name); 

	/**
	  \struct fs_node
	  \brief Filesystem node typedef struct

	  This struct consists of:
		I. name: Filename of the node
		II. mask: The permissions mask
		III. uid: The owning user
		IV. gid: The owning group
		V. Includes the node type. See the FS_* defines in fs.h.
		VI. inode: This is device-specific - provides a way for a filesystem to identify files
		VII. length: Size of the file in bytes
		VIII. An implementation-defined number
		IX. read: Read function, if the node is a file
		X. write: Write function, if the node is a file
		XI. rename: Rename function, if the node is a file
		XII. open: Open function, if the node is a file
		XIII. close: Close function, if the node is a file
		XIV. readdir: Read function, if the node is a directory
		XV. finddir: Find directory function
		XVI. ptr: Used by mountpoints and symbolic links
	*/
	typedef struct fs_node
	{
	   char name[128];
	   uint32_t mask;
	   uint32_t uid;
	   uint32_t gid;
	   uint32_t flags;
	   uint32_t inode;
	   uint32_t length;
	   uint32_t impl;
	   read_type_t read;
	   write_type_t write;
	   rename_type_t rename;
	   open_type_t open;
	   close_type_t close;
	   readdir_type_t readdir;
	   finddir_type_t finddir;
	   struct fs_node *ptr;
	} fs_node_t; 

	/**
	  \struct readdir
	  \brief Filesystem directory entry typedef struct

	  One of these is returned by the readdir call, according to POSIX.

	  This struct consists of:
		I. name: Filename
		II. ino: Inode number. Required by POSIX.
	*/
	struct dirent
	{
	  char name[128]; // Filename.
	  uint32_t ino;     // Inode number. Required by POSIX.
	}; 


	extern fs_node_t *fs_root; // The root of the filesystem.

	uint32_t create_file_fs(char *name, uint8_t *buffer, uint32_t size);

	uint32_t delete_file_fs(char *name);

	void create_dir_fs(char *name);

	uint32_t delete_dir_fs(char *name);

	uint32_t rename_fs(fs_node_t *node, char *name);

	uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);

	uint32_t write_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);

	void open_fs(fs_node_t *node, uint8_t read, uint8_t write);

	void close_fs(fs_node_t *node);

	struct dirent *readdir_fs(fs_node_t *node, uint32_t index);

	fs_node_t *finddir_fs(fs_node_t *node, char *name); 


#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
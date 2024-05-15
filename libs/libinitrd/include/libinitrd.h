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
  \file      initrd.h
  \brief     Initrd support.
  \details   This header file is used for initial ramdisk support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef LIBINITRD_H
#define LIBINITRD_H

#include <libfs.h>
#include <system/types.h>

#define MAX_INITRD_FILES 1000

#if defined(__cplusplus)
extern "C" {
#endif
	fs_node_t *initrd_root;             // Our root directory node.

	/**
	  \struct initrd_header_t
	  \brief Initrd header typedef struct

	  Initial ramdisk header type.

	  This struct consists of:
		I. nfiles: The number of files in the ramdisk.
	*/
	typedef struct
	{
	   uint32_t nfiles; // The number of files in the ramdisk.
	} initrd_header_t;

	/**
	  \struct initrd_file_header_t
	  \brief Initrd file header typedef struct

	  Initial ramdisk file header type.

	  This struct consists of:
		I. magic: The magic number, for error checking
		II. name: The filename
		III. offset Offset in the initial ramdisk that the file starts
		IV. length: Length of the file
	*/
	typedef struct
	{
	   uint8_t magic;     // Magic number, for error checking.
	   int8_t name[64];  // Filename.
	   uint32_t offset;   // Offset in the initrd that the file starts.
	   uint32_t length;   // Length of the file.
	} initrd_file_header_t;


	/**
	   \brief       Standard initrd file creation function

	   Standard initrd file creation function.
	   \param{in}   name The name of the file
	   \param{in}   buffer The buffer of characters to be written, in uint8_t* form.
	   \param{in}   size The size of the new file.
	   \returns The size of the file
	*/
	uint32_t initrd_create_file(char *name, uint8_t *buffer, uint32_t size);

	/**
	   \brief       Standard initrd file deletion function

	   Standard initrd file deletion function.
	   \param{in}   name The name of the file
	   \returns 0 if successful.
	*/
	uint32_t initrd_delete_file(char *name);

	/**
	   \brief       Standard initrd directory creation function

	   Standard initrd directory creation function.
	   \param{in}   name The name of the directory
	*/
	void initrd_create_dir(char *name);

	/**
	   \brief       Standard initrd directory deletion function

	   Standard initrd directory deletion function.
	   \param{in}   name The name of the directory
	   \returns 0 if successful.
	*/
	uint32_t initrd_delete_dir(char *name);


	/**
	   \brief       file renaming function

	   Standard initrd rename function.
	   \param{in}   node The node to write to
	   \param{in}   name The directories new name.
	   \returns 0 if successful.
	*/
	uint32_t initrd_rename_file(fs_node_t *node, const char *name);

	/**
	   \brief       Directory renaming function

	   Standard initrd rename function.
	   \param{in}   node The node to write to
	   \param{in}   name The directories new name.
	   \returns 0 if successful.
	*/
	uint32_t initrd_rename_dir(fs_node_t *node, const char *name);
	/**
	   \brief       Standard initrd write function

	   Standard initrd write function.
	   \param{in}   node The node to write to
	   \param{in}   offset The offset for `node`
	   \param{in}   size The amount of bytes to write after `offset`.
	   \param{in}   buffer The buffer of characters to be written, in uint8_t* form.
	   \returns The size of the buffer.
	*/
	uint32_t initrd_write(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);

	/**
	   \brief       Standard initrd read function

	   Standard initrd read function.
	   \param{in}   node The node to read from
	   \param{in}   offset The offset for `node`
	   \param{in}   size The amount of bytes to read after `offset`.
	   \param{in}   buffer The buffer of characters to be read, in uint8_t* form.
	   \returns The size of the buffer.
	*/
	uint32_t initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
	/**
	   \brief       Standard initrd readdir function

	   Standard initrd read directory function.
	   \param{in}   node The node to read from
	   \param{in}   index The index of the directory.
	   \returns The size of the buffer.
	*/
	struct dirent *initrd_readdir(fs_node_t *node, uint32_t index);
	/**
	   \brief       Standard initrd finddir function

	   Standard initrd find directory function.
	   \param{in}   node The parent node to search from
	   \param{in}   name The name of the directory.
	   \returns The size of the buffer.
	*/
	//todo: the compiler loves to b*tch about the pointers
	//so i need to fix that
	fs_node_t *initrd_finddir(const char *name);

	// Initialises the initial ramdisk. It gets passed the address of the multiboot module,
	// and returns a completed filesystem node.
	fs_node_t *initialise_initrd(uint32_t location);




#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif

//based off the following, heavily modified
/**
  \file      shell.h
  \brief     Provides shell support to the kernel
  \details   Allows the kernel to accept user input and parse it.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __SHELL_SHELL_H
#define __SHELL_SHELL_H

#include <drivers/fs/fs.h>
#include <stdbool.h>

#define NULL ((char *)0)
//#define sizeof(type) (char *)(&type+1)-(char*)(&type)
#define SHELL_VERSION "1.0.0\n"


#if defined(__cplusplus)
extern "C" {
#endif
	extern int enable_shell;

	fs_node_t blank;

	void clear_scr();

	/**
		\brief Initializes the shell
	*/
	void shell_init();

	/**
		\brief Runs the shell
		\param{in} s User input to be parsed
		\param{in} i Cursor X position
	*/
	void shell(char s[], int i);


#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
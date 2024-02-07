/**
  \file      shell.h
  \brief     Provides shell support to the kernel
  \details   Allows the kernel to accept user input and parse it.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __SHELL_H
#define __SHELL_H

#include <fs.h>

#define NULL ((char *)0)
#define sizeof(type) (char *)(&type+1)-(char*)(&type)
#define SHELL_VERSION "1.0.0\n"
#define HELP_APP_ID 1
#define HELP_APP_ID_TW 2
#define ABOUT_APP_ID 3
#define LS_APP_ID 4
#define CAT_APP_ID 5
  
extern int enable_shell;

fs_node_t blank;

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

void avaliable_commands();
void avaliable_commands_two();

#endif
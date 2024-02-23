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
//#define sizeof(type) (char *)(&type+1)-(char*)(&type)
#define SHELL_VERSION "1.0.0\n"

// HELP app ID's
#define HELP_APP_ID 1
#define HELP_APP_ID_TW 2

// ABOUT app ID's
#define ABOUT_APP_ID 3
#define ABOUT_APP_ID_TW 4
#define ABOUT_APP_ID_TH 5

// LS app ID's
#define LS_APP_ID 6
#define LS_APP_ID_TW 7
#define LS_APP_ID_TH 8
//#define LS_APP_ID_FR 9
//#define LS_APP_ID_FV 10
#define LS_APP_ID_SX 11

// CAT app ID's
#define CAT_APP_ID 12
#define CAT_APP_ID_TW 13

// CALC app ID's
#define CALC_APP_ID 14
#define CALC_APP_ID_TW 15
#define CALC_APP_ID_TH 16
#define CALC_APP_ID_FR 17
#define CALC_APP_ID_FV 18

//the calculator holding variables
int calc_num1;
int calc_num2;
int calc_op;

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

void app_info(char *desc, int appid, int box);

void reboot();

void avaliable_commands(int page);

void about(int page);

void ls(int start, int id, int page);

void cat(char s[]);

void shutdown();

void calc(int num1, int num2, int op);

#endif
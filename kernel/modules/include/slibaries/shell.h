
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

#ifndef __SLIBARIES_SHELL_H
#define __SLIBARIES_SHELL_H

#include <drivers/fs/fs.h>

#define NULL ((char *)0)
//#define sizeof(type) (char *)(&type+1)-(char*)(&type)
#define SHELL_VERSION "1.0.0\n"

// HELP app ID's
#define HELP_APP_ID 1
#define HELP_APP_ID_TW 2
#define HELP_APP_ID_TH 3
#define HELP_APP_ID_FR 4
#define HELP_APP_ID_FV 5
#define HELP_APP_ID_SX 6
#define HELP_APP_ID_SV 7
#define HELP_APP_ID_EI 8
#define HELP_APP_ID_NI 9

// ABOUT app ID's
#define ABOUT_APP_ID 10
#define ABOUT_APP_ID_TW 11
#define ABOUT_APP_ID_TH 12
#define ABOUT_APP_ID_FR 13
#define ABOUT_APP_ID_FV 14
#define ABOUT_APP_ID_SX 15
#define ABOUT_APP_ID_SV 16
#define ABOUT_APP_ID_EI 17
#define ABOUT_APP_ID_NI 18

// LS app ID's
#define LS_APP_ID 19
#define LS_APP_ID_TW 20
#define LS_APP_ID_TH 21
#define LS_APP_ID_FR 22
#define LS_APP_ID_FV 23
#define LS_APP_ID_SX 24
#define LS_APP_ID_SV 25
#define LS_APP_ID_EI 26
#define LS_APP_ID_NI 27
#define LS_APP_ID_TN 28

// CAT app ID's
#define CAT_APP_ID 29
#define CAT_APP_ID_TW 30
#define CAT_APP_ID_TH 31
#define CAT_APP_ID_FR 32
#define CAT_APP_ID_FV 33
#define CAT_APP_ID_SX 34
#define CAT_APP_ID_SV 35
#define CAT_APP_ID_EI 36

// CALC app ID's
#define CALC_APP_ID 37
#define CALC_APP_ID_TW 38
#define CALC_APP_ID_TH 39
#define CALC_APP_ID_FR 40
#define CALC_APP_ID_FV 41
#define CALC_APP_ID_SX 42
#define CALC_APP_ID_SV 43
#define CALC_APP_ID_EI 44

//Shell app ID's
#define SHELL_APP_ID 45
#define SHELL_APP_ID_TW 46
#define SHELL_APP_ID_TH 47
#define SHELL_APP_ID_FR 48
#define SHELL_APP_ID_FV 49
#define SHELL_APP_ID_SX 50
#define SHELL_APP_ID_SV 51
#define SHELL_APP_ID_EI 52
#define SHELL_APP_ID_NI 53
#define SHELL_APP_ID_TN 54
#define SHELL_APP_ID_EL 55

//Power app ID's
#define POWER_APP_ID 56
#define POWER_APP_ID_TW 57
#define POWER_APP_ID_TH 58

//Home app ID's
#define HOME_APP_ID 59
#define HOME_APP_ID_TW 60
#define HOME_APP_ID_TH 61

//Warning box ID
#define WARN_BOX_ID 62

//the cmd app ID's
#define CMD_APP_ID 63
#define CMD_APP_ID_TW 64
#define CMD_APP_ID_TH 65
#define CMD_APP_ID_FR 66
#define CMD_APP_ID_FV 67
#define CMD_APP_ID_SX 68
#define CMD_APP_ID_SV 69
#define CMD_APP_ID_EI 70

//the caln app ID's
#define CALN_APP_ID 71
#define CALN_APP_ID_TW 72
#define CALN_APP_ID_TH 73
#define CALN_APP_ID_FR 74
#define CALN_APP_ID_FV 75
#define CALN_APP_ID_SX 76
#define CALN_APP_ID_SV 77
#define CALN_APP_ID_EI 78

//the sett app ID's
#define SETT_APP_ID 79
#define SETT_APP_ID_TW 80
#define SETT_APP_ID_TH 81
#define SETT_APP_ID_FR 82
#define SETT_APP_ID_FV 83
#define SETT_APP_ID_SX 84
#define SETT_APP_ID_SV 85
#define SETT_APP_ID_EI 86

//the calculator holding variables
char calc_buffer[100];
int calc_index;
int calc_num1;
int calc_num2;
int calc_num1_negative;
int calc_num2_negative;
char calc_op;
int input_counter;
int calc_anwser;
char calc_anwser_str;
char prev_anwser_str;


//the cat holding variables
char* lastcatfile;

//the calendar holding variables
int calnpage;

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

void calc(int uim, int selected);

void cmd_init();

void cmd(char* str[]);

void caln(int uim, int selected);

void sett(int uim, int selected);

void tui_shell();

void app_menu(int selected, int uim);

void power_menu(int selected, int uim);

void main_menu(int selected, int uim, int mode);
#endif
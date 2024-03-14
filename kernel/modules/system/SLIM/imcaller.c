// Small Lightweight Interaction Manager
// SLIM Version V1.0.0

#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/mod.h>


void appinput_handler(char c, int userinputmode) {

	if (userinputmode >= HELP_APP_ID && userinputmode <= HELP_APP_ID_NI) {
		helpim(c, userinputmode);
	} else if (userinputmode >= ABOUT_APP_ID && userinputmode <= ABOUT_APP_ID_NI) {
		aboutim(c, userinputmode);
	} else if (userinputmode >= LS_APP_ID && userinputmode <= LS_APP_ID_TN) {
		lsim(c, userinputmode);
	} else if (userinputmode >= CAT_APP_ID && userinputmode <= CAT_APP_ID_EI) {
		catim(c, userinputmode);
	} else if (userinputmode >= CALC_APP_ID && userinputmode <= CALC_APP_ID_EI) {
		calcim(c, userinputmode);
	} else if (userinputmode >= SHELL_APP_ID && userinputmode <= SHELL_APP_ID_EL) {
		shellim(c, userinputmode);
	} else if (userinputmode >= POWER_APP_ID && userinputmode <= POWER_APP_ID_TH) {
		powerim(c, userinputmode);
	} else if (userinputmode >= HOME_APP_ID && userinputmode <= HOME_APP_ID_TH) {
		homeim(c, userinputmode);
	} else if (userinputmode == WARN_BOX_ID) {
		warnim(c, userinputmode);
	} else if (userinputmode >= CMD_APP_ID && userinputmode <= CMD_APP_ID_EI) {
		cmdim(c, userinputmode);
	} else if (userinputmode >= CALN_APP_ID && userinputmode <= CALN_APP_ID_EI) {
		calnim(c, userinputmode);
	} else if (userinputmode >= SETT_APP_ID && userinputmode <= SETT_APP_ID_EI) {
		settim(c, userinputmode);
	}
}


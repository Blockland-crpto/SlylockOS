#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <drivers/vga.h>
#include <slibaries/shell.h>

void appinfo_handler(char c, int appid) {
	if(appid >= HELP_APP_ID && appid <= HELP_APP_ID_TW) {
		if (c == 'a') {
		   app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		}  
	} else if (appid >= ABOUT_APP_ID && appid <= ABOUT_APP_ID_TW) {
		if (c == 'a') {
		   app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		}
	} else if (appid >= LS_APP_ID && appid <= LS_APP_ID_TH) {
		if (c == 'a') {
		   app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		}
	  }
}
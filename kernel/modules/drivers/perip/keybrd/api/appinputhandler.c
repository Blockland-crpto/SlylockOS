#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>




void appinput_handler(char c, int userinputmode) {
	if (userinputmode == HELP_APP_ID) {
		if (c == '<') {
		  //Do nothing
		} else if (c == '>') {
		  avaliable_commands(2);
		}
	  } else if(userinputmode == HELP_APP_ID_TW) {
		if (c == '<') {
		  avaliable_commands(1);
		} else if (c == '>') {
		  //Do nothing
		}
	  } else if(userinputmode == HELP_APP_ID_TH) {
		if (c == 'b') {
			avaliable_commands(1);
		}
	  } else if (userinputmode == ABOUT_APP_ID) {
		  if (c == '<') {
			//Do nothing
		  } else if (c == '>') {
			about(2);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_TW) {
		  if (c == '<') {
			about(1);
		  } else if (c == '>') {
			//Do nothing
		  }
	  } else if (userinputmode == ABOUT_APP_ID_TH) {
		  if (c == 'b') {
			  about(1);
		  }
	  } else if (userinputmode == LS_APP_ID) {
		  if (c == '<') {
			//Do nothing
		  } else if (c == '>') {
			ls(16, LS_APP_ID_TW, 2);
		  }
	  } else if (userinputmode == LS_APP_ID_TW) {
		  if (c == '<') {
			ls(0, LS_APP_ID, 1);
		  } else if (c == '>') {
			ls(32, LS_APP_ID_TH, 3);
		  }
	  } else if (userinputmode == LS_APP_ID_TH) {
		  if (c == '<') {
			ls(16, LS_APP_ID_TW, 2);
		  } else if (c == '>') {
			//Do nothing
		  }
	  } else if (userinputmode == LS_APP_ID_FR)  {
		  if (c == 'b') {
			  ls(0, LS_APP_ID, 1);
		  }
	  } else if (userinputmode == CAT_APP_ID) {
		  if (c == 'a') {
			  app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		  }
	  }
	
}
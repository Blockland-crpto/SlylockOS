#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>




void appinput_handler(char c, int userinputmode) {

	//HELP registry
	if (userinputmode == HELP_APP_ID) {
		//help main page
		if (c == '<') {
		  //Do nothing
		} else if (c == '>') {
		  avaliable_commands(2);
		} else if (c == 'm') {
		  center_menu(HELP_APP_ID_FR, 2);
		}
	  } else if(userinputmode == HELP_APP_ID_TW) {
		//help second page
		if (c == '<') {
		  avaliable_commands(1);
		} else if (c == '>') {
		  //Do nothing
		} else if (c == 'm') {
		  center_menu(HELP_APP_ID_FR, 2);
		}
	  } else if(userinputmode == HELP_APP_ID_TH) {
		//help about screen
		if (c == 'b') {
			avaliable_commands(1);
		} else if (c == 'm') {
			center_menu(HELP_APP_ID_FV, 4);
		}
	  } else if(userinputmode == HELP_APP_ID_FR) {
		//help menu
		if (c == 'b') {
			avaliable_commands(1);
		} else if (c == 'a') {
			app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		}
	  } else if(userinputmode == HELP_APP_ID_FV) {
		//help about menu
		if (c == 'b') {
			app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		} else if(c == 'p') {
			avaliable_commands(1);
		}
		
	  } 
	
		
	  //ABOUT registry
	  else if (userinputmode == ABOUT_APP_ID) {
		  //about main page
		  if (c == '<') {
			//Do nothing
		  } else if (c == '>') {
			about(2);
		  } else if (c == 'm') {
			center_menu(ABOUT_APP_ID_FR, 2);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_TW) {
		  //about second page
		  if (c == '<') {
			about(1);
		  } else if (c == '>') {
			//Do nothing
		  } else if (c == 'm') {
			center_menu(ABOUT_APP_ID_FR, 2);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_TH) {
		  //about about screen
		  if (c == 'b') {
			  about(1);
		  } else if (c == 'm') {
			  center_menu(ABOUT_APP_ID_FV, 4);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_FR) {
		  //about menu
		  if (c == 'b') {
			  about(1);
		  } else if (c == 'a') {
			  app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_FV) {
		  //about about menu
		  if (c == 'b') {
			  app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		  } else if(c == 'p') {
			  about(1);
		  }
	  }

		  
	  //LS registry
	  else if (userinputmode == LS_APP_ID) {
		  //ls first screen
		  if (c == '<') {
			//Do nothing
		  } else if (c == '>') {
			ls(16, LS_APP_ID_TW, 2);
		  } else if (c == 'm') {
			center_menu(LS_APP_ID_FV, 2);
		  }
	  } else if (userinputmode == LS_APP_ID_TW) {
		  //ls second screen
		  if (c == '<') {
			ls(0, LS_APP_ID, 1);
		  } else if (c == '>') {
			ls(32, LS_APP_ID_TH, 3);
		  } else if (c == 'm') {
			center_menu(LS_APP_ID_FV, 2);
		  }
	  } else if (userinputmode == LS_APP_ID_TH) {
		  //ls third screen
		  if (c == '<') {
			ls(16, LS_APP_ID_TW, 2);
		  } else if (c == '>') {
			//Do nothing
		  } else if (c == 'm') {
			center_menu(LS_APP_ID_FV, 2);
		  }
	  } else if (userinputmode == LS_APP_ID_FR)  {
		  //ls about menu
		  if (c == 'b') {
			  ls(0, LS_APP_ID, 1);
		  } else if (c == 'm') {
			  center_menu(LS_APP_ID_SX, 4);
		  }
	  } else if (userinputmode == LS_APP_ID_FV) {
		  //ls menu
		  if (c == 'b') {
			  ls(0, LS_APP_ID, 1);
		  } else if (c == 'a') {
			  app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		  }
	  } else if (userinputmode == LS_APP_ID_SX) {
		  //ls about menu
		  if (c == 'b') {
			  app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		  } else if (c == 'p') {
			  ls(0, LS_APP_ID, 1);
		  }
	  } 
	

	   //CAT registry
	   else if (userinputmode == CAT_APP_ID) {
	      //cat screen
		  if (c == 'm') {
			  center_menu(CAT_APP_ID_TH, 2);
		  }
	  } else if (userinputmode == CAT_APP_ID_TW) {
		  //about cat screen
		  if (c == 'm') {
			  center_menu(CAT_APP_ID_FR, 3);
		  }
	  } else if (userinputmode == CAT_APP_ID_TH) {
		  //cat menu
		  if (c == 'a') {
			  app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		  } 
	  } else if (userinputmode == CAT_APP_ID_FR) {
		  //cat about menu
		  if (c == 'b') {
			  app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		  }
	  }
	
}
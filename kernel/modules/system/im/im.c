#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>

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
		} else if (c == '\n') {
			tui_reset();
		}
	  } else if(userinputmode == HELP_APP_ID_FV) {
		//help about menu
		if (c == 'b') {
			app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		} else if(c == 'p') {
			avaliable_commands(1);
		} else if (c == '\n') {
			tui_reset();
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
		  } else if (c == '\n') {
			  tui_reset();
		  }
	  } else if (userinputmode == ABOUT_APP_ID_FV) {
		  //about about menu
		  if (c == 'b') {
			  app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		  } else if(c == 'p') {
			  about(1);
		  } else if (c == '\n') {
			  tui_reset();
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
		} else if (c == '\n') {
			tui_reset();
		}
	} else if (userinputmode == LS_APP_ID_SX) {
		//ls about menu
		if (c == 'b') {
			app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		} else if (c == 'p') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '\n') {
			tui_reset();
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
		} else if (c == '\n') {
			tui_reset();
		}
	} else if (userinputmode == CAT_APP_ID_FR) {
		//cat about menu
		if (c == 'b') {
			app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		} else if (c == '\n') {
			tui_reset();
		}
	}


	//CALCULATOR registry
	else if (userinputmode == CALC_APP_ID_FR) {
		//calc screen
		if (c == 'm') {
			center_menu(CALC_APP_ID_SX, 2);
		} else if (c == '\n') {
			tui_reset();
		}
	} else if (userinputmode == CALC_APP_ID_SX) {
		//calc menu
		if (c == 'a') {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_SV, 1);
		} else if (c == '\n') {
			tui_reset();
		}
	} else if (userinputmode == CALC_APP_ID_SV) {
		//calc about screen
		if (c == 'm') {
			center_menu(CALC_APP_ID_EI, 3);
		}
	} else if (userinputmode == CALC_APP_ID_EI) {
		//calc about menu
		if (c == 'b') {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_SV, 1);
		} else if (c == '\n') {
			tui_reset();
		}
	}

	//SHELL registry
	else if (userinputmode == SHELL_APP_ID) {
		//the "desktop"
		if (c == 'm') {
			center_menu(SHELL_APP_ID_TW, 5);
		}
	} else if (userinputmode == SHELL_APP_ID_TW) {
		//the main menu
		if (c == 'b') {
			tui_shell();
		} else if (c == 'a') {
			app_menu(1, SHELL_APP_ID_TH);
		}
	} else if (userinputmode == SHELL_APP_ID_TH) {
		//application menu
		if (c == '\n') {
			about(1);
		} else if (c == '}') {
			app_menu(2, SHELL_APP_ID_FR);
		}
	} else if (userinputmode == SHELL_APP_ID_FR) {
		if (c == '\n') {
			avaliable_commands(1);
		} else if (c == '{') {
			app_menu(1, SHELL_APP_ID_TH);
		} else if (c == '}') {
			app_menu(3, SHELL_APP_ID_FV);
		}
	} else if (userinputmode == SHELL_APP_ID_FV) {
		if (c == '\n') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '{') {
			app_menu(2, SHELL_APP_ID_FR);
		} else if (c == '}') {
			app_menu(4, SHELL_APP_ID_SX);
		}
	} else if (userinputmode == SHELL_APP_ID_SX) {
		if (c == '\n') {
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == '{') {
			app_menu(3, SHELL_APP_ID_FV);
		} else if (c == '}') {
			app_menu(5, SHELL_APP_ID_SV);
		}
	} else if (userinputmode == SHELL_APP_ID_SV) {
		if (c == '\n') {
			textbox("Enter the first number", "", CALC_APP_ID);
		} else if (c == '{') {
			app_menu(4, SHELL_APP_ID_SX);
		} else if (c == '}') {
			app_menu(6, SHELL_APP_ID_EI);
		}
	} else if (userinputmode == SHELL_APP_ID_EI) {
		if (c == '\n') {
			tui_reset();
		} else if (c == '{') {
			app_menu(5, SHELL_APP_ID_SV);
		}
	}
}
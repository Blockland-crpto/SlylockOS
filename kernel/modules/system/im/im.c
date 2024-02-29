#include <system/im.h>
#include <slibaries/shell.h>
#include <drivers/perip/keybrd.h>
#include <slibaries/gui.h>
#include <system/mod.h>

// { = up arrow
// } = down arrow

void appinput_handler(char c, int userinputmode) {

	//HELP registry
	if (userinputmode == HELP_APP_ID) {
		//help main page
		if (c == '<') {
		  //Do nothing
		} else if (c == '>') {
		  avaliable_commands(2);
		} else if (c == 'm') {
		  main_menu(1, HELP_APP_ID_FR, 1);
		}
	  } else if(userinputmode == HELP_APP_ID_TW) {
		//help second page
		if (c == '<') {
		  avaliable_commands(1);
		} else if (c == '>') {
		  //Do nothing
		} else if (c == 'm') {
			main_menu(1, HELP_APP_ID_FR, 1);
		}
	  } else if(userinputmode == HELP_APP_ID_TH) {
		//help about screen
		if (c == 'm') {
			main_menu(1, HELP_APP_ID_SV, 2);
		}
	  } else if(userinputmode == HELP_APP_ID_FR) {
		//help menu
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, HELP_APP_ID_FV, 1);
		}
		
	  } else if(userinputmode == HELP_APP_ID_FV) {
		//help menu if about is selected
		if (c == '\n') {
			app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		} else if (c == '{') {
			main_menu(1, HELP_APP_ID_FR, 1);
		} else if (c == '}') {
			main_menu(3, HELP_APP_ID_SX, 1);
		}
 
	  } else if(userinputmode == HELP_APP_ID_SX) {
		//help menu if back is selected
		if (c == '\n') {
			avaliable_commands(1);
		} else if (c == '{') {
			main_menu(2, HELP_APP_ID_FV, 1);
		}

	  } else if (userinputmode == HELP_APP_ID_SV) {
		//help about menu
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, HELP_APP_ID_EI, 2);
		}
	  } else if (userinputmode == HELP_APP_ID_EI) {
		//help about menu if back is selected
		if (c == '\n') {
			app_info("Help\nthe Help app for MINIOS\nVersion 1.0.0", HELP_APP_ID_TH, 2);
		} else if (c == '{') {
			main_menu(1, HELP_APP_ID_SV, 2);
		} else if (c == '}') {
			main_menu(3, HELP_APP_ID_NI, 2);
		}
	  } else if (userinputmode == HELP_APP_ID_NI) {
		//help about menu if back to app is selected
		if (c == '\n') {
			avaliable_commands(1);
		} else if (c == '}') {
			main_menu(2, HELP_APP_ID_EI, 2);
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
			main_menu(1, ABOUT_APP_ID_FR, 1);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_TW) {
		  //about second page
		  if (c == '<') {
			about(1);
		  } else if (c == '>') {
			//Do nothing
		  } else if (c == 'm') {
			main_menu(1, ABOUT_APP_ID_FR, 1);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_TH) {
		  //about about screen
		  if (c == 'm') {
			  main_menu(1, ABOUT_APP_ID_SV, 2);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_FR) {
		  //about menu if exit app is selected
		  if (c == '\n') {
			  tui_reset();
		  } else if (c == '}') {
			  main_menu(2, ABOUT_APP_ID_FV, 1);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_FV) {
		  //about menu if about is selected
		  if (c == '\n') {
			  app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		  } else if (c == '{') {
			  main_menu(1, ABOUT_APP_ID_FR, 1);
		  } else if (c == '}') {
			  main_menu(3, ABOUT_APP_ID_SX, 1);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_SX) {
		  //about menu if back is selected
		  if (c == '\n') {
			  about(1);
		  } else if (c == '{') {
			  main_menu(2, ABOUT_APP_ID_FV, 1);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_SV) {
		  //about about menu if exit app is selected
		  if (c == '\n') {
			  tui_reset();
		  } else if (c == '}') {
			  main_menu(2, ABOUT_APP_ID_EI, 2);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_EI) {
		  //about about menu if back is selected
		  if (c == '\n') {
			  app_info("About\nthe system info for MINIOS\nVersion 1.0.0", ABOUT_APP_ID_TH, 2);
		  } else if (c == '{') {
			  main_menu(1, ABOUT_APP_ID_SV, 2);
		  } else if (c == '}') {
			  main_menu(3, ABOUT_APP_ID_NI, 2);
		  }
	  } else if (userinputmode == ABOUT_APP_ID_NI) {
		  //about about menu if back to app is selected
		  if (c == '\n') {
			  about(1);
		  } else if (c == '{') {
			  main_menu(2, ABOUT_APP_ID_EI, 2);
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
			main_menu(1, LS_APP_ID_FV, 1);
		  }
	} else if (userinputmode == LS_APP_ID_TW) {
		//ls second screen
		if (c == '<') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '>') {
			ls(32, LS_APP_ID_TH, 3);
		} else if (c == 'm') {
			main_menu(1, LS_APP_ID_FV, 1);
		}
	} else if (userinputmode == LS_APP_ID_TH) {
		//ls third screen
		if (c == '<') {
			ls(16, LS_APP_ID_TW, 2);
		} else if (c == '>') {
		//Do nothing
		} else if (c == 'm') {
			main_menu(1, LS_APP_ID_FV, 1);
		}
	} else if (userinputmode == LS_APP_ID_FR)  {
		//ls about menu
		if (c == 'm') {
			main_menu(1, LS_APP_ID_EI, 2);
		}
	} else if (userinputmode == LS_APP_ID_FV) {
		//ls menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, LS_APP_ID_SX, 1);
		}
	} else if (userinputmode == LS_APP_ID_SX) {
		//ls menu if About is selected
		if (c == '\n') {
			app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		} else if (c == '{') {
			main_menu(1, LS_APP_ID_FV, 1);
		} else if (c == '}') {
			main_menu(3, LS_APP_ID_SV, 1);	
		}
	} else if (userinputmode == LS_APP_ID_SV) {
		//ls menu if back is selected
		if (c == '\n') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '{') {
			main_menu(2, LS_APP_ID_SX, 1);
		}
	} else if (userinputmode == LS_APP_ID_EI) {
		//ls about menu if exit is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, LS_APP_ID_NI, 2);
		}
	} else if (userinputmode == LS_APP_ID_NI) {
		//ls about menu if back is selected
		if (c == '\n') {
			app_info("Ls\nthe file manager for MINIOS\nVersion 1.0.0", LS_APP_ID_FR, 2);
		} else if (c == '{') {
			main_menu(1, LS_APP_ID_EI, 2);
		} else if (c == '}') {
			main_menu(3, LS_APP_ID_TN, 2);
		}
	} else if (userinputmode == LS_APP_ID_TN) {
		//ls about menu if back to app is selected
		if (c == '\n') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '{') {
			main_menu(2, LS_APP_ID_NI, 2);
		}
	}


	//CAT registry
	else if (userinputmode == CAT_APP_ID) {
		//cat screen
		if (c == 'm') {
			main_menu(1, CAT_APP_ID_TH, 1);
		}
	} else if (userinputmode == CAT_APP_ID_TW) {
		//about cat screen
		if (c == 'm') {
			main_menu(1, CAT_APP_ID_SX, 2);
		}
	} else if (userinputmode == CAT_APP_ID_TH) {
		//cat menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CAT_APP_ID_FR, 1);
		}
	} else if (userinputmode == CAT_APP_ID_FR) {
		//cat menu if about is selected
		if (c == '\n') {
			app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		} else if (c == '{') {
			main_menu(1, CAT_APP_ID_TH, 1);
		} else if (c == '}') {
			main_menu(3, CAT_APP_ID_FV, 1);
		}
	} else if (userinputmode == CAT_APP_ID_FV) {
		//cat menu if back is selected
		if (c == '\n') {
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == '{') {
			main_menu(2, CAT_APP_ID_FR, 1);
		}
	} else if (userinputmode == CAT_APP_ID_SX) {
		//cat about menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CAT_APP_ID_SV, 2);
		}
	} else if (userinputmode == CAT_APP_ID_SV) {
		//cat about menu if back is selected
		if (c == '\n') {
			app_info("Cat\nthe text file viewer for MINIOS\nVersion 1.0.0", CAT_APP_ID_TW, 1);
		} else if (c == '{') {
			main_menu(1, CAT_APP_ID_SX, 2);
		} else if (c == '}') {
			main_menu(3, CAT_APP_ID_EI, 2);
		}
	} else if (userinputmode == CAT_APP_ID_EI) {
		//cat about menu if back to app is selected
		if (c == '\n') {
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == '{') {
			main_menu(2, CAT_APP_ID_SV, 2);
		}
	}


	//CALCULATOR registry
	else if (userinputmode == CALC_APP_ID_FR) {
		//calc screen
		if (c == 'm') {
			main_menu(1, CALC_APP_ID_SV, 1);
		} else if (c == '\n') {
			tui_reset();
		}
	} else if (userinputmode == CALC_APP_ID_SX) {
		//calc about screen
		if (c == 'm') {
			main_menu(1, CALC_APP_ID_TN, 2);
		}
	} else if (userinputmode == CALC_APP_ID_SV) {
		//calc menu if Exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CALC_APP_ID_EI, 1);
		}
	} else if (userinputmode == CALC_APP_ID_EI) {
		//calc menu if about is selected
		if (c == '\n') {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_SX, 1);
		} else if (c == '{') {
			main_menu(1, CALC_APP_ID_SV, 1);
		} else if (c == '}') {
			main_menu(3, CALC_APP_ID_NI, 1);
		}
	} else if (userinputmode == CALC_APP_ID_NI) {
		//calc menu if back is selected
		if (c == '\n') {
			textbox("Enter the first number", "", CALC_APP_ID);
		} else if (c == '{') {
			main_menu(2, CALC_APP_ID_EI, 1);
		}
	} else if (userinputmode == CALC_APP_ID_TN) {
		//calc about menu if exit app is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '}') {
			main_menu(2, CALC_APP_ID_EL, 2);
		}
	} else if (userinputmode == CALC_APP_ID_EL) {
		//calc about menu if back is selected
		if (c == '\n') {
			app_info("Calculator\nthe calculator app for MINIOS\nVersion 1.0.0", CALC_APP_ID_SX, 1);
		} else if (c == '{') {
			main_menu(1, CALC_APP_ID_TN, 2);
		} else if (c == '}') {
			main_menu(3, CALC_APP_ID_TL, 2);
		}
	} else if (userinputmode == CALC_APP_ID_TL) {
		//calc about menu if back to app is selected
		if (c == '\n') {
			textbox("Enter the first number", "", CALC_APP_ID);
		} else if (c == '{') {
			main_menu(2, CALC_APP_ID_EL, 2);
		}
	}

		

	//SHELL registry
	else if (userinputmode == SHELL_APP_ID) {
		//the "desktop"
		if (c == 'm') {
			main_menu(1, HOME_APP_ID, 3);
		}
	} else if (userinputmode == SHELL_APP_ID_TH) {
		//application menu
		if (c == '\n') {
			about(1);
		} else if (c == '}') {
			app_menu(2, SHELL_APP_ID_FR);
		}
	} else if (userinputmode == SHELL_APP_ID_FR) {
		//application menu if help is selected
		if (c == '\n') {
			avaliable_commands(1);
		} else if (c == '{') {
			app_menu(1, SHELL_APP_ID_TH);
		} else if (c == '}') {
			app_menu(3, SHELL_APP_ID_FV);
		}
	} else if (userinputmode == SHELL_APP_ID_FV) {
		//application menu if ls is selected
		if (c == '\n') {
			ls(0, LS_APP_ID, 1);
		} else if (c == '{') {
			app_menu(2, SHELL_APP_ID_FR);
		} else if (c == '}') {
			app_menu(4, SHELL_APP_ID_SX);
		}
	} else if (userinputmode == SHELL_APP_ID_SX) {
		//application menu if cat is selected
		if (c == '\n') {
			textbox("cat", "Enter the file location", CAT_APP_ID);
		} else if (c == '{') {
			app_menu(3, SHELL_APP_ID_FV);
		} else if (c == '}') {
			app_menu(5, SHELL_APP_ID_SV);
		}
	} else if (userinputmode == SHELL_APP_ID_SV) {
		//application menu if calculator is selected
		if (c == '\n') {
			textbox("Enter the first number", "", CALC_APP_ID);
		} else if (c == '{') {
			app_menu(4, SHELL_APP_ID_SX);
		} else if (c == '}') {
			app_menu(6, SHELL_APP_ID_EI);
		}
	} else if (userinputmode == SHELL_APP_ID_EI) {
		//application menu if exit is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '{') {
			app_menu(5, SHELL_APP_ID_SV);
		}
	}

	//POWER registry
	else if (userinputmode == POWER_APP_ID) {

		
		if (c == '\n') {
			shutdown();
		} else if (c == '}') {
			power_menu(2, POWER_APP_ID_TW);
		}
	} else if (userinputmode == POWER_APP_ID_TW) {
		if (c == '\n') {
			reboot();
		} else if (c == '}') {
			power_menu(3, POWER_APP_ID_TH);
		} else if (c == '{') {
			power_menu(1, POWER_APP_ID);
		}
	} else if (userinputmode == POWER_APP_ID_TH) {
		if (c == '\n') {
			tui_reset();
		} else if (c == '{') {
			power_menu(2, POWER_APP_ID_TW);
		}
	}

	//HOME Registry
	else if (userinputmode == HOME_APP_ID) {
		//home menu when poweroptions is selected
		if (c == '\n') {
			power_menu(1, POWER_APP_ID);
		} else if (c == '}') {
			main_menu(2, HOME_APP_ID_TW, 3);
		}
	} else if (userinputmode == HOME_APP_ID_TW) {
		//home menu when applicatons is selected
		if (c == '\n') {
			app_menu(1, SHELL_APP_ID_TH);
		} else if (c == '}') {
			main_menu(3, HOME_APP_ID_TH, 3);
		} else if (c == '{') {
			main_menu(1, HOME_APP_ID, 3);
		}
	} else if (userinputmode == HOME_APP_ID_TH) {
		//home menu when back is selected
		if (c == '\n') {
			tui_reset();
		} else if (c == '{') {
			main_menu(2, HOME_APP_ID_TW, 3);
		}
	}
}

void im_init() {
	module_t modules_im_im = MODULE("kernel.modules.im.im", "the interaction manager for the kernel (CORE)");
	tui_shell();
}
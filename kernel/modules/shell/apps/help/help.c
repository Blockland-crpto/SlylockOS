#include <shell.h>
#include <keyboard.h>
#include <gui.h>

//Help main page
void avaliable_commands(int page){
  char helpstrpgo[235] ="Avaliable Commands\n\n`help` Shows this screen.\n\n`clear` Clears the screen\n\n`about` Shows information about the OS.\n\n`reboot` Reboots the computer.\n\n`cat <[Any] file>` Prints the contents of the file `file`.";
  char helpstrpgt[200] = "Avaliable Commands\n\n`ls` Prints a list of all the files and directories\n in the current directory.\n\n`shutdown` Shuts down the computer.\n\n`calc` Opens a calculator.";
  if (page == 1) {
	userinputmode = HELP_APP_ID;
	make_gui(3, 3, 1, 2);
	make_gui_windows("", helpstrpgo, 3, 3, 70, 22);
  } else if (page == 2) {
	userinputmode = HELP_APP_ID_TW;
	make_gui(3, 3, 2, 2);
	make_gui_windows("", helpstrpgt, 3, 3, 70, 22);
  }

}
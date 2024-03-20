#include <shell/shell.h>
#include <drivers/perip/keybrd.h>
#include <libtui.h>
#include <system/kernel.h>


//Help main page
void avaliable_commands(int page){
  char helpstrpgo[235] ="Avaliable apps\n\n`help` Shows this screen.\n\n`about` Shows information about the OS.\n\n`power options` shows power options.\n\n`cat` Prints the contents of a file.\n\n`cmd` opens the command line.";
  char helpstrpgt[230] = "Avaliable apps\n\n`files` Prints a list of all the files and directories\n\n`calculator` Opens a calculator.\n\n`calendar` opens a calendar app\n\n`settings` opens the settings app.";
  if (page == 1) {
	userinputmode = HELP_APP_ID;
	make_tui(themeindex, themeindex, 1, 2);
	make_tui_windows("", helpstrpgo, 3, 3, 70, 20);
  } else if (page == 2) {
	userinputmode = HELP_APP_ID_TW;
	make_tui(themeindex, themeindex, 2, 2);
	make_tui_windows("", helpstrpgt, 3, 3, 70, 20);
  }

}
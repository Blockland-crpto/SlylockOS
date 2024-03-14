#include <drivers/vga.h>
#include <libtui.h>
#include <drivers/perip/keybrd.h>
#include <string.h>
#include <slibaries/shell.h>
#include <stdio.h>
#include <stdbool.h>
#include <drivers/perip/timer.h>
#include <system/kernel.h>

void sett(int uim, int selected) {
	userinputmode = uim;
	make_tui(themeindex, themeindex, 0, 0);
	make_tui_windows("SETT", "", 3, 3, 70, 20);

	// show the theme option
	putstrpos("Theme", 7, 7, 8, 7, 7);
	button("<-", 27, 6, 3, 1, false);
	button("->", 32, 6, 3, 1, false);

	
	if (selected == 0) {
	} else if (selected == 1) {
		//if the right arrow is pressed
		button("->", 32, 6, 3, 1, true);
		time_sleep(400000);
		if (themeindex == 15) {
			themeindex = 0;	
		} else if (themeindex == 6) {
			themeindex++;
			themeindex++;
		} else {
			themeindex++;
		}
		
		
		sett(uim, 10);
	} else if (selected == 2) {
		//if the left arrow is pressed
		button("<-", 27, 6, 3, 1, true);
		time_sleep(400000);
		if (themeindex == 0) {
			themeindex = 15;
		} else if (themeindex == 8) {
			themeindex--;
			themeindex--;
		} else {
			themeindex--;
		}
	
		sett(uim, 10);
	}
}
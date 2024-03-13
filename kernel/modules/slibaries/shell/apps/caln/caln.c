#include <drivers/vga.h>
#include <slibaries/gui.h>
#include <drivers/perip/keybrd.h>
#include <string.h>
#include <slibaries/shell.h>
#include <stdio.h>
#include <drivers/perip/timer.h>
#include <system/kernel.h>
#include <stdbool.h>

void caln(int uim, int selected) {
	int daysinmonth;
	userinputmode = uim;

	make_gui(themeindex, themeindex, 0, 0);
	make_gui_windows("CALN", "", 3, 3, 70, 20);

	if (calnpage == 0) {
		putstrpos("January", 32, 4, 8, 7, 32);
		daysinmonth = 31;
	} else if (calnpage == 1) {
		putstrpos("February", 32, 4, 8, 7, 32);
		daysinmonth = 29;
	} else if (calnpage == 2) {
		putstrpos("March", 32, 4, 8, 7, 32);
		daysinmonth = 31;
	} else if (calnpage == 3) {
		putstrpos("April", 32, 4, 8, 7, 32);
		daysinmonth = 30;
	} else if (calnpage == 4) {
		putstrpos("May", 32, 4, 8, 7, 32);
		daysinmonth = 31;
	} else if (calnpage == 5) {
		putstrpos("June", 32, 4, 8, 7, 32);
		daysinmonth = 30;
	} else if (calnpage == 6) {
		putstrpos("July", 32, 4, 8, 7, 32);
		daysinmonth = 31;
	} else if (calnpage == 7) {
		putstrpos("August", 32, 4, 8, 7, 32);
		daysinmonth = 31;
	} else if (calnpage == 8) {
		putstrpos("September", 32, 4, 8, 7, 32);
		daysinmonth = 30;
	} else if (calnpage == 9) {
		putstrpos("October", 32, 4, 8, 7, 32);
		daysinmonth = 31;
	} else if (calnpage == 10) {
		putstrpos("November", 32, 4, 8, 7, 32);
		daysinmonth = 30;
	} else if (calnpage == 11) {
		putstrpos("December", 32, 4, 8, 7, 32);
		daysinmonth = 31;
	}


	button("<-", 3, 1, 3, 1, false);
	button("->", 67, 1, 3, 1, false);
	
	for (int x = 8; x < 65; x++) {
		putpos('#', 8, 8, x, 8);
		putpos('#', 8, 8, x, 10);
		putpos('#', 8, 8, x, 12);
		putpos('#', 8, 8, x, 14);
		putpos('#', 8, 8, x, 16);
		putpos('#', 8, 8, x, 18);
	}

	for (int y = 8; y < 19; y++) {
		putpos('#', 8, 8, 8, y);
		putpos('#', 8, 8, 16, y);
		putpos('#', 8, 8, 24, y);
		putpos('#', 8, 8, 32, y);
		putpos('#', 8, 8, 40, y);
		putpos('#', 8, 8, 48, y);
		putpos('#', 8, 8, 56, y);
		putpos('#', 8, 8, 64, y);
	}


	putpos('1', 8, 7, 9, 9);
	putpos('2', 8, 7, 17, 9);
	putpos('3', 8, 7, 25, 9);
	putpos('4', 8, 7, 33, 9);
	putpos('5', 8, 7, 41, 9);
	putpos('6', 8, 7, 49, 9);
	putpos('7', 8, 7, 57, 9);
	
	putpos('8', 8, 7, 9, 11);
	putpos('9', 8, 7, 17, 11);
	putstrpos("10", 25, 11, 8, 7, 25);
	putstrpos("11", 33, 11, 8, 7, 33);
	putstrpos("12", 41, 11, 8, 7, 41);
	putstrpos("13", 49, 11, 8, 7, 49);
	putstrpos("14", 57, 11, 8, 7, 57);

	putstrpos("15", 9, 13, 8, 7, 9);
	putstrpos("16", 17, 13, 8, 7, 17);
	putstrpos("17", 25, 13, 8, 7, 25);
	putstrpos("18", 33, 13, 8, 7, 33);
	putstrpos("19", 41, 13, 8, 7, 41);
	putstrpos("20", 49, 13, 8, 7, 49);
	putstrpos("21", 57, 13, 8, 7, 57);

	putstrpos("22", 9, 15, 8, 7, 9);
	putstrpos("23", 17, 15, 8, 7, 17);
	putstrpos("24", 25, 15, 8, 7, 25);
	putstrpos("25", 33, 15, 8, 7, 33);
	putstrpos("26", 41, 15, 8, 7, 41);
	putstrpos("27", 49, 15, 8, 7, 49);
	putstrpos("28", 57, 15, 8, 7, 57);
	putstrpos("29", 9, 17, 8, 7, 9);

	if (daysinmonth == 31) {
		putstrpos("30", 17, 17, 8, 7, 17);
		putstrpos("31", 25, 17, 8, 7, 25);

	} else if (daysinmonth == 30) {
		putstrpos("30", 17, 17, 8, 7, 17);
	}

	if (selected == 1) {
		button("<-", 3, 1, 3, 1, true);
		time_sleep(600000);
		if (calnpage == 0) {
			calnpage = 11;
		} else {
			calnpage--;
		}
		caln(uim, 0);
	} else if (selected == 2) {
		button("->", 67, 1, 3, 1, true);
		time_sleep(600000);
		if (calnpage == 11) {
			calnpage = 0;
		} else {
			calnpage++;
		}
		caln(uim, 0);
	}
}
#include <slibaries/gui.h>
#include <slibaries/shell.h>
#include <drivers/vga.h>
#include <drivers/perip/keybrd.h>

void center_menu(int uim, int opts) {
	userinputmode = uim;
	for (int x = 20; x < 50; x++) {
		for (int y = 1; y < 9; y++) {
			putpos("#", 7, 7, x, y);
		}
	}

	for (int y = 2; y < 9; y++) {
		putpos("#", 8, 8, 49, y);
		putpos("#", 8, 8, 20, y);
	}

	for (int x = 20; x < 50; x++) {
		putpos("#", 8, 8, x, 8);
	}
	putstrpos("MiniOS", 30, 1, 8, 7, 30);

	if (opts == 1) {
		putstrpos("Enter: Exit App", 21, 2, 8, 7, 21);
	} else if (opts == 2) {
		putstrpos("Enter: Exit App", 21, 2, 8, 7, 21);
		putstrpos("A: About App", 21, 3, 8, 7, 21);
	} else if (opts == 3) {
		putstrpos("Enter: Exit App", 21, 2, 8, 7, 21);
		putstrpos("B: Back", 21, 3, 8, 7, 21);
	} else if (opts == 4) {
		putstrpos("Enter: Exit App", 21, 2, 8, 7, 21);
		putstrpos("B: Back", 21, 3, 8, 7, 21);
		putstrpos("P: Back to previous menu", 21, 4, 8, 7, 21);
	} else if (opts == 5) {
		putstrpos("Enter: Power Options", 21, 2, 8, 7, 21);
		putstrpos("A: Applications", 21, 3, 8, 7, 21);
		putstrpos("B: Back", 21, 4, 8, 7, 21);
	}
}
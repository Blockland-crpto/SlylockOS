#include <drivers/vga.h>
#include <drivers/perip/timer.h>
#include <slibaries/gui.h>

void loading_bar_two(int len, int startx, int starty) {

	for (int x = startx; x < startx + len; x++) {
		putpos('#', 8, 8, x, starty);
		putpos('#', 8, 8, x, starty + 2);
	}

	for (int y = starty; y < starty + 3; y++) {
		putpos('#', 8, 8, startx, y);
		putpos('#', 8, 8, startx + len, y);
	}


	//todo: fix the last row error
	
	for (int j = 0; j < 10; j++) {
		for (int i = 1; i < len-1; i++) {
			int currentx = startx + i;
			putpos('#', 1, 1, currentx, starty + 1);
			if (i > 1) {
				putpos('#', 7, 7, currentx - 1, starty + 1);
			}
			time_sleep(6000000);
		}

		for (int i = len-1; i > 0; i--) {
			int currentx = startx + i;
			int insidelen = len - 1;
			
			putpos('#', 1, 1, currentx, starty + 1);
			if (currentx < startx + insidelen) {
				putpos('#', 7, 7, currentx + 1, starty + 1);
			}
			
			time_sleep(6000000);
		}
	} 
}
#include <screen.h>
#include <gui.h>
#include <timer.h>

void loading_bar(int len, int startx, int starty, int delay) {

	for (int x = startx; x < startx + len; x++) {
		putpos('#', 8, 8, x, starty);
		putpos('#', 8, 8, x, starty + 2);
	}

	for (int y = starty; y < starty + 3; y++) {
		putpos('#', 8, 8, startx, y);
		putpos('#', 8, 8, startx + len, y);
	}

	for (int i = 1; i < len; i++) {
		putpos('#', 1, 1, startx + i, starty + 1);
		time_sleep(delay);
	}

}
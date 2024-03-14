#include <libtui.h>
#include <drivers/vga.h>
#include <stdbool.h>

void button(char* cont, int x, int y, int w, int h, bool selected) {
	int color1;
	int color2;
	if (selected == false) {
		color1 =  COLOR_DGY;
		color2 = COLOR_GRY;
	} else if (selected == true) {
		color1 = COLOR_BLU;
		color2 = COLOR_WHT;
	}
	
	for (int i = x; i < x+w+1; i++) {
	
		putpos('#', color1, color1, i, y);
		putpos('#', color1, color1, i, y+h);
	}

	for (int i = y; i < y+h+1; i++) {
		putpos('#', color1, color1, x, i);
		putpos('#', color1, color1, x+w, i);
	}

	putstrpos(cont, x, y+1, color1, color2, x);
	
}
#include <slibaries/gui.h>
#include <drivers/vga.h>

void make_gui(int winfg, int winbg, int multipage, int exitopt) {
  for(int y = 0; y<2; y++) {
	for(int x = 0; x<80; x++) {
	  putpos("#", 7, 7, x, y);
	}
  }
  if (exitopt == 1) {
	  putstrpos("Enter = Exit", 2, 1, 8, 7, 2);
  } else if (exitopt == 2) {
	  putstrpos("Enter = Exit | A = About", 2, 1, 8, 7, 2);
  } else if (exitopt == 3) {
	  putstrpos("Enter = Exit | B = Back", 2, 1, 8, 7, 2);
  }
  
	
  for(int y = 25; y > 1; y--) {
	for(int x = 0; x<80; x++) {
	  putpos("#", winfg, winbg, x, y);
	}
  }

  for (int i = 0; i < multipage; i++) {
	  putpos("=", 8, 7, 49 + i, 1);
  }
  return 0;
}

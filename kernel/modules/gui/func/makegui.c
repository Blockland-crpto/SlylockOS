#include <gui.h>
#include <screen.h>

void make_gui(int winfg, int winbg, int multipage) {
  for(int y = 0; y<2; y++) {
	for(int x = 0; x<80; x++) {
	  putpos("#", 7, 7, x, y);
	}
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

#include <libtui.h>
#include <drivers/vga.h>
#include <string.h>
#include <drivers/perip/rtc.h>

void make_tui(int winfg, int winbg, int multipage, int exitopt) {

	
  for(int y = 0; y<2; y++) {
	for(int x = 0; x<80; x++) {
	  putpos('#', 7, 7, x, y);
	}
  }
  
  putstrpos("|Main|", 30, 1, 8, 7, 30);
	
  for(int y = 25; y > 1; y--) {
	for(int x = 0; x<80; x++) {
	  putpos('#', winfg, winbg, x, y);
	}
  }

  for (int y = 25; y > 23; y--) {
	  for (int x = 0; x < 80; x++) {
		  putpos('#', 7, 7, x, y);
	  }
  }
	
  putstrpos("Ctrl: Menu", 5, 24, 8, 7, 10);
	
  for (int i = 0; i < multipage; i++) {
	  putpos('=', 8, 7, 49 + i, 1);
  }
  return 0;
}

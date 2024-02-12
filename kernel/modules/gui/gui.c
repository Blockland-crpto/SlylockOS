#include <gui.h>
#include <screen.h>

void make_gui_windows(char *title, char *cont, int beginx, int beginy, int endx, int endy) {
  for(int y = beginy; y < endy; y++) {
	for(int x = beginx; x < endx; x++) {
	  putpos("#", 7, 7, x, y);
	}
  }

  for(int x = beginx; x < endx; x++) {
	putpos("#", 8, 7, x, endy);
	putpos("#", 8, 7, x, beginy);
  }
  for(int y = beginy; y < endy+1; y++) 
  {
	putpos("#", 8, 7, beginx, y);
	putpos("#", 8, 7, endx, y);
  }
  putstrpos(title, beginx+1, beginy+1, 8, 7, beginx+1);
  putstrpos(cont, beginx+1, beginy+3, 8, 7, beginx+1);
  return 0;
}

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
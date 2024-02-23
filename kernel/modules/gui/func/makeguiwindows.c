#include <gui.h>
#include <screen.h>

void make_gui_windows(char *title, char *cont, int beginx, int beginy, int endx, int endy) {
  for(int y = beginy; y < endy; y++) {
	for(int x = beginx; x < endx; x++) {
	  putpos("#", 7, 7, x, y);
	}
  }

  for(int x = beginx; x < endx; x++) {
	putpos("#", 8, 8, x, endy);
	putpos("#", 8, 8, x, beginy);
  }
  for(int y = beginy; y < endy+1; y++) 
  {
	putpos("#", 8, 8, beginx, y);
	putpos("#", 8, 8, endx, y);
  }
  putstrpos(title, beginx+1, beginy+1, 8, 7, beginx+1);
  putstrpos(cont, beginx+1, beginy+3, 8, 7, beginx+1);
  return 0;
}
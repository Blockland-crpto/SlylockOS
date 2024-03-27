#include <libvga.h>
#include <libssp.h>

void color_screen(int fg, int bg) {
  for(int y = 0; y<25; y++) {
	for(int x = 0; x<80; x++) {
	  putpos("#", fg, bg, x, y);
	}
  }
}
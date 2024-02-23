#include <screen.h>
#include <string.h>



void putstrpos(const char *string, unsigned char x, unsigned char y, unsigned char fg_color, unsigned char bg_color, int start) {
  for (int i = 0; i < strlen(string); i++) {
	if (string[i] == '\n') {
	  x = start;
	  y++;
	}
	x++;
	putpos(string[i], fg_color, bg_color, x, y);
  }
}
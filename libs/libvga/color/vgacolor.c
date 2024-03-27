#include <libvga.h>
#include <libssp.h>

unsigned char vga_color(const unsigned char fg_color, const unsigned char bg_color){
	// Put bg color in the higher 4 bits and mask those of fg
	return (bg_color << 4) | (fg_color & 0x0F);
}

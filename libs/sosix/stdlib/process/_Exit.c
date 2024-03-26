#include <stdlib.h>
#include <libssp.h>
#include <drivers/vga.h>
#include <drivers/perip/keybrd.h>

void _Exit(int status) {
	kprintf("Exiting\n");
}
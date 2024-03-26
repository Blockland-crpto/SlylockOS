#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>
#include <drivers/vga.h>
#include <drivers/perip/keyboard.h>

void exit(int status) {
	kprintf("Exiting");
}
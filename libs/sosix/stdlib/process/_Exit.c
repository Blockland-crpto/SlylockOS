#include <stdlib.h>
#include <libssp.h>
#include <libvga.h>
#include <libkeyboard.h>

void _Exit(int status) {
	kprintf("Exiting\n");
}
#include <stdlib.h>
#include <stddef.h>
#include <libssp.h>
#include <libvga.h>
#include <libkeyboard.h>

void exit(int status) {
	kprintf("Exiting");
}
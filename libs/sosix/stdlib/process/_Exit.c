#include <stdlib.h>
#include <libssp.h>
#include <libvga.h>
#include <libproc.h>
#include <libkeyboard.h>

void _Exit(int status) {

	//lets kill the current process
	proc_kill();
}
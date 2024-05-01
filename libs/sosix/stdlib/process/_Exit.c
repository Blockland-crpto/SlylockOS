#include <stdlib.h>
#include <libssp.h>
#include <libvga.h>
#include <libproc.h>
#include <libkeyboard.h>

void _Exit(int status) {
	//lets exit the process
	proc_control_block current_task = task_queue[0];

	//destroyes the process
	proc_destroy(current_task.id);

	//exiting
	kprintf("Exiting\n");
}
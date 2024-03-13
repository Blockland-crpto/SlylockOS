#include <drivers/vga.h>
#include <drivers/x86/isr.h>
#include <drivers/perip/timer.h>
#include <drivers/io/ports.h>
#include <string.h>
#include <system/mod.h>
#include <system/task.h>

#define FREQ 100

//The timer has 3 channels, 0,1,2
//0 is for IRQ0
//1 is system specific and 2 is for speaker
//2 can be used to create sound like
//these three channels are present at 0x40, 0x41, 0x42 and 0x43 is the command register

//let's keep track of number of ticks elapsed
int ticks = 0;
int seconds = 0;


//to increase the "ticks" variable, we increment it evrytime the timer fires.
//the timer PIT is connected to IRQ0, so evrytime it fires, we increment it
//by default, the timer fires 18.222 times/second.
void timer_handler(struct regs *r){
    //increment number of ticks
    ticks++;
    if(ticks % FREQ == 0){
        seconds++;
    }
}

//let's install timer handler into IRQ0
void timer_install(){
	create_task("timer_installer", TASK_PRIORITY_KERNEL, TASK_ID_KERNEL);
    module_t modules_timer_timer = MODULE("kernel.modules.timer.timer", "Adds PIT support for the kernel (CORE)");
	char** deps;
	deps[0] = "kernel.modules.isr.isr";
	deps[1] = "kernel.modules.irq.irq";
	DEPS(modules_timer_timer, deps);
    timer_phase(FREQ);
    irq_install_handler(0, timer_handler);
    INIT(modules_timer_timer);
	modify_task(TASK_STATE_ENDED);
}

void timer_wait(int val){
    unsigned int end = seconds + val;
    while(seconds < end){
        asm volatile("" : : : "memory");
    }
}

int get_tracked_seconds() {
	return seconds;
}


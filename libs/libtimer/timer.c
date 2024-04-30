/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libvga.h>
#include <libdmgctrl.h>
#include <libtimer.h>
#include <libports.h>
#include <string.h>
#include <libmodule.h>
#include <libssp.h>

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
    module_t modules_timer = MODULE("kernel.modules.timer", "Adds PIT support for the kernel (CORE)");
	char** deps;
	deps[0] = "kernel.modules.isr";
	deps[1] = "kernel.modules.irq";
	INIT(modules_timer);
	DEPS(modules_timer, deps);
    timer_phase(FREQ);
    irq_install_handler(0, timer_handler);
   	DONE(modules_timer);
	 
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


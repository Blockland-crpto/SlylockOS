#include <libtimer.h>
#include <libports.h>
#include <libssp.h>

//set the phase of the timer
//the value divisor is sent into the PIT to make it divide its
//frequency by this divisor, so that we get the exact clock frequency
void timer_phase(int hz){
	//create the divisor to send into the clock
	int divisor = 1193180/hz;
	//send the command byte
	outb(0x43, 0x36);

	//now these are the upper lower bytes of the divisor
	//they need to be split before they are sent.
	outb(0x40, divisor & 0xFF);
	outb(0x40, divisor >> 8);
}
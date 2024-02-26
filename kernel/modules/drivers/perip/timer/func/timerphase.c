#include <drivers/perip/timer.h>
#include <drivers/io/ports.h>

//set the phase of the timer
//the value divisor is sent into the PIT to make it divide its
//frequency by this divisor, so that we get the exact clock frequency
void timer_phase(int hz){
	//create the divisor to send into the clock
	int divisor = 1193180/hz;
	//send the command byte
	out_port_byte(0x43, 0x36);

	//now these are the upper lower bytes of the divisor
	//they need to be split before they are sent.
	out_port_byte(0x40, divisor & 0xFF);
	out_port_byte(0x40, divisor >> 8);
}
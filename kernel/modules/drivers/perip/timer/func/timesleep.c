#include <drivers/perip/timer.h>

void time_sleep(int time) {
	for(int i = 0; i < time; i++) {
		__asm__ __volatile__("sti");
	}
}
#include <shell.h>
#include <screen.h>
#include <ports.h>


void reboot(){
	clear_scr();
	kprintf("Rebooting...\n");
	//using 8042 keyboard controller to pulse the CPU's RESET Pin
	unsigned char temp = 0x02;
	while(temp & 0x02)
		temp = in_port_byte(0x64);
	out_port_byte(0x64, 0xFE);
	asm volatile("hlt");	
}
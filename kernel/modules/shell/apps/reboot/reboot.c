#include <shell/shell.h>
#include <drivers/vga.h>
#include <drivers/io/ports.h>

void reboot(){
	clear_scr();
	loadingscreen("Restarting", "SlylockOS is Restarting...");
	//using 8042 keyboard controller to pulse the CPU's RESET Pin
	unsigned char temp = 0x02;
	while(temp & 0x02)
		temp = in_port_byte(0x64);
	out_port_byte(0x64, 0xFE);
	asm volatile("hlt");	
}
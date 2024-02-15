#include <nmi.h>
#include <ports.h>
#include <modules.h>


void nmi_enable() {
	out_port_byte(0x70, in_port_byte(0x70) & 0x7F);
	in_port_byte(0x71);
}

void nmi_disable() {
	out_port_byte(0x70, in_port_byte(0x70) | 0x80);
	in_port_byte(0x71);
}
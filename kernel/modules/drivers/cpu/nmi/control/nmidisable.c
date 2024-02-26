#include <drivers/cpu/nmi.h>
#include <drivers/io/ports.h>

void nmi_disable() {
	out_port_byte(0x70, in_port_byte(0x70) | 0x80);
	in_port_byte(0x71);
}
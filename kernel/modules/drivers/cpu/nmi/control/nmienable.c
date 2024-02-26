#include <drivers/cpu/nmi.h>
#include <drivers/io/ports.h>

void nmi_enable() {
	out_port_byte(0x70, in_port_byte(0x70) & 0x7F);
	in_port_byte(0x71);
}
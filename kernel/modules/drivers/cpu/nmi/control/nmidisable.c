#include <drivers/cpu/nmi.h>
#include <drivers/io/ports.h>
#include <system/debug.h>
#include <libssp.h>

void nmi_disable() {
	if (nmi_enabled) {
		out_port_byte(0x70, in_port_byte(0x70) | 0x80);
		in_port_byte(0x71);
		nmi_enabled = false;
	} else {
		warn("Oops, nmi_disable() called when nmi was not enabled!");
	}
	
}
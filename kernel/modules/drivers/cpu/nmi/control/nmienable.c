#include <drivers/cpu/nmi.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <system/debug.h>
#include <libssp.h>

void nmi_enable() {
	if (!nmi_enabled) {
		out_port_byte(0x70, in_port_byte(0x70) & 0x7F);
		in_port_byte(0x71);
		nmi_enabled = true;
	} else {
		warn("Oops! NMI is already enabled!");
	}
	
}
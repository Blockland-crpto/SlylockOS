#include <drivers/nmi.h>
#include <libports.h>
#include <system/types.h>
#include <libdebug.h>
#include <libssp.h>

void nmi_enable() {
	if (!nmi_enabled) {
		outb(0x70, inb(0x70) & 0x7F);
		inb(0x71);
		nmi_enabled = true;
	} else {
		warn("Oops! NMI is already enabled!");
	}
	
}
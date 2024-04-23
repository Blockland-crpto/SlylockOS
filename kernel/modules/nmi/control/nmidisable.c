#include <drivers/nmi.h>
#include <libports.h>
#include <libdebug.h>
#include <libssp.h>

void nmi_disable() {
	if (nmi_enabled) {
		outb(0x70, inb(0x70) | 0x80);
		inb(0x71);
		nmi_enabled = false;
	} else {
		warn("Oops, nmi_disable() called when nmi was not enabled!");
	}
	
}
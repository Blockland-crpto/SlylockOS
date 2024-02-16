#include <drivers/nmi.h>
#include <ports.h>
#include <modules.h>
#include <types.h>

void nmi_init() {
	module_t modules_nmi_nmi = MODULE("kernel.modules.nmi.nmi", "provides a handler for non maskable interrupts (CORE)");
	nmi_enable();
	INIT(modules_nmi_nmi);
}

void nmi_enable() {
	out_port_byte(0x70, in_port_byte(0x70) & 0x7F);
	in_port_byte(0x71);
}

void nmi_disable() {
	out_port_byte(0x70, in_port_byte(0x70) | 0x80);
	in_port_byte(0x71);
}

uint32_t retrive_nmi_data_a() {
	uint32_t nmi_cause_a;
	nmi_cause_a = in_port_byte(0x92);
	return nmi_cause_a;
}

uint32_t retrive_nmi_data_b() {
	uint32_t nmi_cause_b;
	nmi_cause_b = in_port_byte(0x61);
	return nmi_cause_b;
}
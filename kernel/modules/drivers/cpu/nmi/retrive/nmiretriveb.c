#include <drivers/cpu/nmi.h>
#include <drivers/io/ports.h>
#include <system/types.h>

uint32_t retrive_nmi_data_b() {
	uint32_t nmi_cause_b;
	nmi_cause_b = in_port_byte(0x61);
	return nmi_cause_b;
}
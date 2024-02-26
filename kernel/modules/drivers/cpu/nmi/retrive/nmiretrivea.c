#include <drivers/cpu/nmi.h>
#include <drivers/io/ports.h>
#include <system/types.h>

uint32_t retrive_nmi_data_a() {
	uint32_t nmi_cause_a;
	nmi_cause_a = in_port_byte(0x92);
	return nmi_cause_a;
}
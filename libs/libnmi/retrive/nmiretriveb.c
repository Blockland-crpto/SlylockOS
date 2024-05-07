#include <libnmi.h>
#include <libports.h>
#include <system/types.h>
#include <libssp.h>

uint32_t retrive_nmi_data_b() {
	uint32_t nmi_cause_b;
	nmi_cause_b = inb(0x61);
	return nmi_cause_b;
}
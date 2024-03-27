#ifndef __DRIVERS_CPU_NMI_H
#define __DRIVERS_CPU_NMI_H

#include <system/types.h>

#if defined(__cplusplus)
extern "C" {
#endif
	void nmi_init();

	bool nmi_enabled;

	void nmi_enable();

	void nmi_disable();

	uint32_t retrive_nmi_data_a();
	uint32_t retrive_nmi_data_b();
#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif 
#ifndef __DRIVERS_NMI_H
#define __DRIVERS_NMI_H

#include <types.h>

void nmi_init();

void nmi_enable();

void nmi_disable();

uint32_t retrive_nmi_data_a();
uint32_t retrive_nmi_data_b();

#endif 
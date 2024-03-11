#ifndef __DRIVERS_PERIP_PCI_H
#define __DRIVERS_PERIP_PCI_H

#include <system/types.h>




typedef struct pciDevice {
	uint8_t bus;
	uint8_t device;
	uint8_t func;
	//uint8_t pclass;
	uint32_t vendor;
} pciDevice_t;

pciDevice_t pciDevMap[70000];


uint32_t pciReadDevice(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg);
void pci_init();



#endif
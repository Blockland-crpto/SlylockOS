#ifndef __DRIVERS_PCI_H
#define __DRIVERS_PCI_H

#include <types.h>




typedef struct pciDevice {
	uint8_t bus;
	uint8_t device;
	uint8_t func;
	uint32_t vendor;
} pciDevice_t;

pciDevice_t pciDevMap[70000];


uint32_t pciReadDevice(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg);
void pci_init();

//uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
//uint16_t pciCheckVendor(uint8_t bus, uint8_t slot);



#endif
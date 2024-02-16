#include <drivers/pci.h>
#include <ports.h>
#include <types.h>
#include <screen.h>
#include <modules.h>

uint32_t config_addr = 0xCF8;
uint32_t config_data = 0xCFC;
uint32_t enable_bit = 0x80000000;


// A reader for pci ports
uint32_t pciReadDevice(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg) {
	outl(enable_bit | (bus << 16) | (device << 11) | (func << 8) | (pcireg << 2), config_addr);
	uint32_t ret = inl(config_data);
	return ret;
}

// PCI init
void pci_init() {
	module_t modules_pci_pci = MODULE("kernel.modules.pci.pci", "Provides PCI support for the kernel (CORE)");
	
	uint8_t bus, device, func;
	uint32_t data;
	int i = 0;
	for (bus = 0; bus != 0xff; bus++) {
		for (device = 0; device < 32; device++) {
			for (func = 0; func < 8; func++) {
				data = pciReadDevice(bus, device, func, 0);
				if(data != 0xFFFF) {
					pciDevMap[i].bus = bus;
					pciDevMap[i].device = device;
					pciDevMap[i].func = func;
					pciDevMap[i].vendor = data;
					i++;
				} 
			}
		}
	}

	INIT(modules_pci_pci);
}
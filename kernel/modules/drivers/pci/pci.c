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

// PCI init (just a printer for now)
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


/*
uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
	uint32_t address;
	uint32_t lbus  = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)func;
	uint16_t tmp = 0;

	// Create configuration address as per Figure 1
	address = (uint32_t)((lbus << 16) | (lslot << 11) |
			  (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));

	// Write out the address
	outl(0xCF8, address);
	// Read in the data
	// (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
	tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
	return tmp;
}

uint16_t pciCheckVendor(uint8_t bus, uint8_t slot) {
	uint16_t vendor, device;
	/* Try and read the first configuration register. Since there are no
	 * vendors that == 0xFFFF, it must be a non-existent device. /*
	if ((vendor = pciConfigReadWord(bus, slot, 0, 0)) != 0xFFFF) {
	   device = pciConfigReadWord(bus, slot, 0, 2);
	}
	
	return (vendor);
}
*/



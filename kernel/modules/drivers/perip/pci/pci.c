#include <drivers/perip/pci.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <drivers/vga.h>
#include <system/mod.h>
#include <stdio.h>
#include <libssp.h>

uint32_t config_addr = 0xCF8;
uint32_t config_data = 0xCFC;
uint32_t enable_bit = 0x80000000;


// A reader for pci ports
uint32_t pciReadDevice(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg) {
	outl(enable_bit | (bus << 16) | (device << 11) | (func << 8) | (pcireg << 2), config_addr);
	uint32_t ret = inl(config_data);
	return ret;
}

// A pciclass retriver
uint8_t pciReadClass(uint8_t bus, uint8_t device, uint8_t func) {
	return (pciReadDevice(bus, device, func, 0xB) >> 24) & 0xFF;
}

// A pcisubclass retriver
uint8_t pciReadSubclass(uint8_t bus, uint8_t device, uint8_t func) {
	return (pciReadDevice(bus, device, func, 0xB) >> 16) & 0xFF;
}

// A pciProgIF retriver
uint8_t pciReadProgif(uint8_t bus, uint8_t device, uint8_t func) {
	return pciReadDevice(bus, device, func, 0xB) & 0xFF;
}

void pci_scan_bus(uint8_t bus) {
	uint8_t device, func;
	uint32_t data;
	int i = 0;
	for (device = 0; device < 32; device++) {
		for (func = 0; func < 8; func++) {
			data = pciReadDevice(bus, device, func, 0);
			if(data != 0xFFFF) {
				pciDevMap[i].bus = bus;
				pciDevMap[i].device = device;
				pciDevMap[i].func = func;
				pciDevMap[i].vendor = data;
				pciDevMap[i].classCode = pciReadClass(bus, device, func);
				pciDevMap[i].subClass = pciReadSubclass(bus, device, func);
				pciDevMap[i].progIF = pciReadProgif(bus, device, func);
				//printf("bus %x, Device %x, Func %x, Vendor %x, Class %x, Subclass %x, progIF %x\n", bus, device, func, data, pciDevMap[i].classCode, pciDevMap[i].subClass, pciDevMap[i].progIF);
				//time_sleep(1000000);
				i++;
			} 
		}
	}
	// Recursively scan subordinate buses
	for (device = 0; device < 32; device++) {
		data = pciReadDevice(bus, device, 0, 0);
		if(data != 0xFFFF && (pciReadClass(bus, device, 0) == 0x06) && (pciReadSubclass(bus, device, 0) == 0x04)) {
			uint8_t secondary_bus = pciReadProgif(bus, device, 0);
			if (secondary_bus != 0) { // Check if secondary bus is valid
				pci_scan_bus(secondary_bus);
			}
		}
	}
}

void pci_init() {
	module_t modules_pci_pci = MODULE("kernel.modules.pci.pci", "Provides PCI support for the kernel (CORE)");

	pci_scan_bus(0); // Start scanning from bus 0

	INIT(modules_pci_pci);
	 
}
/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libpci.h>
#include <libports.h>
#include <stdint.h>
#include <stdbool.h>
#include <libvga.h>
#include <libmodule.h>
#include <stdio.h>
 
#include <libdebug.h>
#include <libdevmgr.h>

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
				//slog("bus %x, Device %x, Func %x, Vendor %x, Class %x, Subclass %x, progIF %x\n", bus, device, func, data, pciDevMap[i].classCode, pciDevMap[i].subClass, pciDevMap[i].progIF);
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
	module_t modules_pci = MODULE("kernel.modules.pci", "Provides PCI support for the kernel (CORE)");

	//let the power initalization begin!
	INIT(modules_pci);

	//lets see if the devmgr has anything to say
	if(devmgr_authorize_device(DEVICE_TYPE_PCI)) {
		pci_scan_bus(0); // Start scanning from bus 0
	}

	//were done!
	DONE(modules_pci);
	 
}
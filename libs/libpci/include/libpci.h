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
#ifndef __LIBPCI_H
#define __LIBPCI_H

#include <system/types.h>

#if defined(__cplusplus)
extern "C" {
#endif
	typedef struct pciDevice {
		uint8_t bus;
		uint8_t device;
		uint8_t func;
		uint8_t classCode;
		uint8_t subClass;
		uint8_t progIF;
		uint32_t vendor;
	} pciDevice_t;

	pciDevice_t pciDevMap[70000];


	uint32_t pciReadDevice(uint8_t bus, uint8_t device, uint8_t func, uint8_t pcireg);
	void pci_init();


#if defined(__cplusplus)
} /* extern "C" */
#endif





#endif
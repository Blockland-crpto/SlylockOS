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
#ifndef __LIBDEVMGR_H__
#define __LIBDEVMGR_H__

#include <system/types.h>

enum device_type {
	DEVICE_TYPE_ISA = 0,
	DEVICE_TYPE_PCI = 1,
	DEVICE_TYPE_CMOS = 2,
	DEVICE_TYPE_8042 = 3,
	DEVICE_TYPE_VGA = 4,
	DEVICE_TYPE_MSI = 5,
};

#if defined(__cplusplus)
extern "C" {
#endif

	//a IA_BOOT_ARCH parsed object
	typedef struct {
		bool isa_supported;
		bool ctrler_8042_supported;
		bool vga_present;
		bool msi_unsupported;
		bool pcie_ctrls_supported;
		bool cmos_not_present;
	} ia_boot_arch_t;

	//the current boot configuration
	ia_boot_arch_t boot_cfg;
	
	//Device manager initalization function
	void devmgr_init();

	//device manager authorization request
	bool devmgr_authorize_device(enum device_type dev);
	
#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
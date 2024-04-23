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
#ifndef __LIBACPI_H__
#define __LIBACPI_H__

#include <system/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

	unsigned long *SMI_CMD;
	signed char ACPI_ENABLE;
	signed char ACPI_DISABLE;
	unsigned long *PM1a_CNT;
	unsigned long *PM1b_CNT;
	uint16_t SLP_TYPa;
	uint16_t SLP_TYPb;
	uint16_t SLP_EN;
	uint16_t SCI_EN;
	signed char PM1_CNT_LEN;

	struct RSDPtr {
	   signed char Signature[8];
	   signed char CheckSum;
	   signed char OemID[6];
	   signed char Revision;
	   unsigned long *RsdtAddress;
	};

	struct FACP {
	   signed char Signature[4];
	   unsigned long Length;
	   signed char unneded1[40 - 8];
	   unsigned long *DSDT;
	   signed char unneded2[48 - 44];
	   unsigned long *SMI_CMD;
	   signed char ACPI_ENABLE;
	   signed char ACPI_DISABLE;
	   signed char unneded3[64 - 54];
	   unsigned long *PM1a_CNT_BLK;
	   unsigned long *PM1b_CNT_BLK;
	   signed char unneded4[89 - 72];
	   signed char PM1_CNT_LEN;
	};

	struct MADT {
	   signed char Signature[4];
	   unsigned long Length;
	   signed char Revision;
	   signed char CheckSum;
	   signed char OemID[6];
	   uint32_t localApicAddr;
	};

	unsigned int *acpiCheckRSDPtr(uint32_t *ptr);
	unsigned int *acpiGetRSDPtr(void);
	int acpiCheckHeader(uint32_t *ptr, char *sig);
	int acpiEnable(void);
	int initAcpi(void);
	void acpiPowerOff(void);
	void acpi_init();
	bool acpiEnabled;


#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
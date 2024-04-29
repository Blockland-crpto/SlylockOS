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

	//acpi data
	int8_t PREFERED_PM_PROFILE;
	int16_t SCI_INT;
	unsigned long *SMI_CMD;
	int8_t ACPI_ENABLE;
	int8_t ACPI_DISABLE;
	int8_t S4BIOS_REQ;
	unsigned long *PM1a_CNT;
	unsigned long *PM1b_CNT;
	uint16_t SLP_TYPa;
	uint16_t SLP_TYPb;
	uint16_t SLP_EN;
	uint16_t SCI_EN;
	int8_t PM1_CNT_LEN;

	struct RSDPtr {
		int8_t Signature[8];
		int8_t CheckSum;
		int8_t OemID[6];
		int8_t Revision;
	  	unsigned long *RsdtAddress;
	};
	
	struct FACP {
		int8_t Signature[4];
	   	unsigned long Length;
		int8_t unneded1[36 - 8];
	   	unsigned long *FIRMWARE_CTRL;
	   	unsigned long *DSDT;
		int8_t reserved;
		int8_t Preferred_PM_Profile;
		int16_t SCI_INT;
	   	unsigned long *SMI_CMD;
	   	int8_t ACPI_ENABLE;
		int8_t ACPI_DISABLE;
		int8_t S4BIOS_REQ;
		int8_t unneded3[64 - 55];
	   	unsigned long *PM1a_CNT_BLK;
	   	unsigned long *PM1b_CNT_BLK;
		int8_t unneded4[89 - 72];
		int8_t PM1_CNT_LEN;
	};

	struct MADT {
		int8_t Signature[4];
	   	unsigned long Length;
		int8_t Revision;
		int8_t CheckSum;
		int8_t OemID[6];
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
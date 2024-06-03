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

#include <stdint.h>
#include <stdbool.h>
#include <libdevmgr.h>


#if defined(__cplusplus)
extern "C" {
#endif

	//structure representing a general Address structure
	struct GAS {
		int8_t Address_space_id;
		int8_t Register_bit_width;
		int8_t Register_bit_offset;
		int8_t Access_size;
		uint64_t Register_address;
	};


	//structure representing a usable GAS
	struct GAS_usable {
		int8_t Address_space_id;
		int8_t Register_bit_width;
		int8_t Register_bit_offset;
		int8_t Access_size;
		uint32_t Register_address;
	};

	//structure representing a ACPI header
	struct acpi_header {
		int8_t Signature[4];
		uint32_t Length;
		int8_t Revision;
		int8_t Checksum;
		int8_t Oem_id[6];
		int8_t Oem_table_id[8];
		uint32_t Oem_revision;
		int8_t Creator_id[4];
		uint32_t Creator_revision;
	};

	//structure representing a ACPI subtable header
	struct acpi_subheader {
		int8_t type;
		int8_t length;
	};

	//structure representing a LAPIC table
	struct MADT_LAPIC {
		struct acpi_subheader subheader;
		int8_t acpi_processor_uid;
		int8_t apic_id;
		uint32_t flags; 
	};

	//structure representing a IOAPIC table
	struct MADT_IOAPIC {
		struct acpi_subheader subheader;
		int8_t io_apic_id;
		int8_t reserved;
		uint32_t io_apic_address;
		uint32_t global_system_interrupt_base;
	};
	
	//FADT info
	int8_t PREFERED_PM_PROFILE;
	int16_t SCI_INT;
	uint32_t *SMI_CMD;
	int8_t ACPI_ENABLE;
	int8_t ACPI_DISABLE;
	int8_t S4BIOS_REQ;
	int8_t PSTATE_CNT;
	uint32_t *PM1a_EVT;
	uint32_t *PM1b_EVT;
	uint32_t *PM1a_CNT;
	uint32_t *PM1b_CNT;
	uint32_t *PM2_CNT;
	uint32_t *PM_TMR;
	uint32_t *GPE0;
	uint32_t *GPE1;
	int8_t PM1_EVT_LEN;
	int8_t PM1_CNT_LEN;
	int8_t PM2_CNT_LEN;
	int8_t PM_TMR_LEN;
	int8_t GPE0_LEN;
	int8_t GPE1_LEN;
	int8_t GPE1_BASE;
	int16_t P_LVL2_LAT;
	int16_t P_LVL3_LAT;
	int16_t FLUSH_SIZE;
	int16_t FLUSH_STRIDE;
	int8_t DUTY_OFFSET;
	int8_t DUTY_WIDTH;
	int8_t DAY_ALRM;
	int8_t MON_ALRM;
	int8_t CENTURY;
	int16_t IAPC_BOOT_ARCH;
	uint32_t FADT_FLAGS;
	struct GAS_usable RESET_REG;
	int8_t reset_value;

	//MADT data
	int8_t GLOBAL_SYSTEM_INT;
	int16_t MPS_INTI_FLAGS;
	
	//ACPI commands
	uint16_t SLP_TYPa;
	uint16_t SLP_TYPb;
	uint16_t SLP_EN;
	uint16_t SCI_EN;
	int8_t CST_CNT;

	unsigned int *acpiCheckRSDPtr(uint32_t *ptr);
	unsigned int *acpiGetRSDPtr(void);
	int acpiCheckHeader(uint32_t *ptr, char *sig);
	int acpiEnable(void);
	int load_acpi(void);
	void acpiPowerOff(void);
	void acpi_init();
	ia_boot_arch_t ia_boot_parser();
	bool acpiEnabled;
	

	//saw this in linux kernel, figured we should do the same
	#pragma pack(1)
	
	struct RSDPtr {
		int8_t Signature[8];
		int8_t CheckSum;
		int8_t OemID[6];
		int8_t Revision;
	  	uint32_t *RsdtAddress;
	};

	struct FACP {
		struct acpi_header header;
		uint32_t *FIRMWARE_CTRL;
		uint32_t *DSDT;
		int8_t reserved;
		int8_t Preferred_PM_Profile;
		int16_t SCI_INT;
		uint32_t *SMI_CMD;
		int8_t ACPI_ENABLE;
		int8_t ACPI_DISABLE;
		int8_t S4BIOS_REQ;
		int8_t PSTATE_CNT;
		uint32_t *PM1a_EVT_BLK;
		uint32_t *PM1b_EVT_BLK;
		uint32_t *PM1a_CNT_BLK;
		uint32_t *PM1b_CNT_BLK;
		uint32_t *PM2_CNT_BLK;
		uint32_t *PM_TMR_BLK;
		uint32_t *GPE0_BLK;
		uint32_t *GPE1_BLK;
		int8_t PM1_EVT_LEN;
		int8_t PM1_CNT_LEN;
		int8_t PM2_CNT_LEN;
		int8_t PM_TMR_LEN;
		int8_t GPE0_BLK_LEN;
		int8_t GPE1_BLK_LEN;
		int8_t GPE1_BASE;
		int8_t CST_CNT;
		int16_t P_LVL2_LAT;
		int16_t P_LVL3_LAT;
		int16_t FLUSH_SIZE;
		int16_t FLUSH_STRIDE;
		int8_t DUTY_OFFSET;
		int8_t DUTY_WIDTH;
		int8_t DAY_ALRM;
		int8_t MON_ALRM;
		int8_t CENTURY;
		int16_t IAPC_BOOT_ARCH;
		int8_t Reserved2;
		uint32_t Flags;
		struct GAS reset_reg;
		int8_t RESET_VALUE;
		int8_t unneeded[244-131];
	};

	struct FACS {
		int8_t Signature[4];
		uint32_t Length;
		int8_t Hardware_signature[4];
		uint32_t* Firmware_waking_vector;
	};
	
	struct MADT {
		struct acpi_header header;
		uint32_t *local_apic_address;
		uint32_t flags;	
	};

	#pragma pack()

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
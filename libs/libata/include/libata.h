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
#ifndef __LIBATA_H
#define __LIBATA_H

#include <system/types.h>
#include <libports.h>
#include "cmdset.h"

//Status of the ATA Device
enum ata_device_status {
	STATUS_ERR = 0x01,
	STATUS_IDX = 0x02,
	STATUS_CORR = 0x04,
	STATUS_DRQ = 0x08,
	STATUS_SRV = 0x10,
	STATUS_DF = 0x20,
	STATUS_RDY = 0x40,
	STATUS_BSY = 0x80,
};

//ATA Error Codes
enum ata_error_codes {
	ERROR_AMNF = 0x01,
	ERROR_TKZNF = 0x02,
	ERROR_ABRT = 0x04,
	ERROR_MCR = 0x08,
	ERROR_IDNF = 0x10,
	ERROR_MC = 0x20,
	ERROR_UNC = 0x40,
	ERROR_BBK = 0x80,
};

//Drive and Head Register Values
enum ata_drive_and_head_register_values {
	LBA_24_BIT = 0x01,
	LBA_25_BIT = 0x02,
	LBA_26_BIT = 0x04,
	LBA_27_BIT = 0x08,
	DAH_DRV = 0x10,
	DAH_1 = 0x20,
	DAH_LBA = 0x40,
	DAH_2 = 0x80,
};

//Device Control Register
enum ata_device_control_registers {
	DEV_CTRL_NA1 = 0x01,
	DEV_CTRL_nlEN = 0x02,
	DEV_CTRL_SRST = 0x04,
	DEV_CTRL_NA2 = 0x08,
	DEV_CTRL_NA3 = 0x10,
	DEV_CTRL_NA4 = 0x20,
	DEV_CTRL_NA5 = 0x40,
	DEV_CTRL_HOB = 0x80,
};

//Drive Address Register
enum ata_drive_address_registers {
	DRV_ADDR_DS0 = 0x01,
	DRV_ADDR_DS1 = 0x02,
	DRV_ADDR_HS0 = 0x04,
	DRV_ADDR_HS1 = 0x08,
	DRV_ADDR_HS2 = 0x10,
	DRV_ADDR_HS3 = 0x20,
	DRV_ADDR_WTG = 0x40,
	DRV_ADDR_NA = 0x80,
};

//IO ports registers
enum ata_io_ports_registers {
	IO_PORT_DATA = 0x1F0,
	IO_PORT_ERROR = 0x1F1,
	IO_PORT_FEATURE = 0x1F1,
	IO_PORT_SECTOR_COUNT = 0x1F2,
	IO_PORT_SECTOR_NUMBER = 0x1F3,
	IO_PORT_CYL_LOW = 0x1F4,
	IO_PORT_CYL_HIGH = 0x1F5,
	IO_PORT_DRIVE_HEAD = 0x1F6,
	IO_PORT_STATUS = 0x1F7,
	IO_PORT_COMMAND = 0x1F7,
};


//Control ports registers
enum ata_ctrl_ports_registers {
	CTRL_ALTERNATE_STATUS = 0x3F6,
	CTRL_DEVICE = 0x3F6,
	CTRL_DRIVE_ADDRESS = 0x3F7,
};

//ATA Device Master
enum ata_device_select {
	SELECT_DEVICE_MASTER = 0xA0,
	SELECT_DEVICE_SLAVE = 0xB0,
};

//ATAPI byte command types
enum atapi_byte_command_types {
	ATAPI_CMD_BYTE_12BYTES = 0,
	ATAPI_CMD_BYTE_16BYTES = 1,
};

//ATA Device Write Addresses (LBA28)
#define DEVICE_MASTER_LBA28 0xE0
#define DEVICE_SLAVE_LBA28 0xF0

//ATA Device Write Addresses (LBA48)
#define DEVICE_MASTER_LBA48 0x40
#define DEVICE_SLAVE_LBA48 0x50

//ATA drive types
enum ata_drive_type {
	DRIVE_TYPE_MASTER = 0,
	DRIVE_TYPE_SLAVE = 1
};

//times to set DRQ
enum atapi_drq_set_times {
	DRQ_SET_TIMES_3MS = 0,
	DRQ_SET_TIMES_50MICROS = 1,
};

//ATA power management
#define DRIVE_STANDBY_IMMEDIATE 0xE0

#if defined(__cplusplus)
extern "C" {
#endif

	//a structure representing a UDMA mode
	typedef struct {
		int id;
		bool supported;
	} udma_mode_t;

	//a structure representing a MDMA mode
	typedef struct {
		int id;
		bool supported;
	} mdma_mode_t;

	//a structure representing a PIO mode
	typedef struct {
		int id;
		bool supported;
	} pio_mode_t;

	//a structure representing ATAPI information
	typedef struct {
		//Is it ATAPI?
		bool is_atapi;
	
		//the atapi cmd packet size
		enum atapi_byte_command_types atapi_cmd_packet_size;

		//the time to set drq
		enum atapi_drq_set_times atapi_drq_set_times;

		//feature set supported
		cmd_set_t feature_set_supported[10];
	
	} atapi_info_t;

	
	//a structure representing a ATA harddrive
	typedef struct {

		//Does it exist?
		bool exists;

		//The drivetype
		enum ata_drive_type driveType;

		//ATAPI info
		atapi_info_t atapi_info;
	
		//Is it removable?
		bool removable;

		//Manufacturer information
		uint16_t serial_number[8];
		uint16_t firmware_revision[2];
		uint16_t model_number[20];
	
		//Iordy information
		bool iordy_supported;
		bool iordy_disabled;
	
		//LBA modes
		bool lba_supported;
		bool lba48_enabled;
		bool lba28_enabled;

		//DMA support
		bool dma_supported;
	
		//UDMA modes
		udma_mode_t supported_udma[7];
		udma_mode_t active_udma;

		//MDMA modes
		mdma_mode_t supported_mdma[2];
		mdma_mode_t active_mdma;

		//PIO modes
		pio_mode_t supported_pio[7];

		//Command set supported information
		cmd_set_t cmd_set_supported[36];
	
		//Standby timer information
		bool standby_timer_enabled;
		bool min_standby_timer_enabled;

		//Transfer time information
		uint16_t min_mdma_transfer_time_per_word;
		uint16_t min_mdma_transfer_time_vendor;
		uint16_t min_pio_transfer_time_no_flow_ctrl;
		uint16_t min_pio_transfer_time_iordy_flow_ctrl;
	
		//Addressable space information
		uint32_t addressable_space_lba28;
		uint64_t addressable_space_lba48;

		//Security information
		uint16_t time_required_for_security_erase;
		uint16_t time_required_secure_erase_enhanced;
		uint16_t master_password_revision_code;
	
		//Misc information
		int major_ata_version;
		uint16_t minor_ata_version;
		bool pin80_connector;
		uint8_t max_queue_depth;
		uint8_t sectors_per_interrupt_rw_multiple;
		bool set_features_spinup_needed;
		uint16_t current_apm_value;
		uint16_t* identify_data_ptr;

	} ata_device_t;
	
	//a array representing the ATA drives
	ata_device_t ata_drives[2];

	ata_device_t ata_identify(enum ata_device_select dev);

	//the main function for reading
	void sect_read_atapio(uint32_t target_address, uint64_t LBA, uint16_t sector_count, ata_device_t* dev);

	//the main function for writing
	void sect_write_atapio(uint64_t LBA, uint16_t sector_count, uint32_t* bytes, ata_device_t* dev);

	//function to wait for the ata device to be ready
	int wait_ata_bsy();

	//function to wait for drive to be idle
	void wait_ata_drq();

	//error handler for the ATA driver
	void ata_error_handler();

	//function to reset the ata drive
	void ata_reset();

	//function to put ATA into standby
	void ata_standby();


	//CFA FUNCTIONS
	//function to use the CFA erase sectors
	void cfa_erase_sectors(uint32_t LBA, uint8_t sector_count, ata_device_t* dev);

	//function to get a extended errorcode
	uint8_t cfa_req_ext_error_code(ata_device_t* dev);

	//function to get the CFA erase data of sectors
	uint8_t* cfa_translate_sector(ata_device_t* dev, uint32_t LBA);

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
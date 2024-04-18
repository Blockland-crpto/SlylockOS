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

//ATA power management
#define DRIVE_STANDBY_IMMEDIATE 0xE0

//ATA supported array key
enum ata_supported_array_key {
	NOP_SUPPORTED = 0,
	READ_BUFFER_SUPPORTED = 1,
	WRITE_BUFFER_SUPPORTED = 2,
	HOST_PROTECTED_AREA_SUPPORTED = 3,
	DEVICE_RESET_SUPPORTED = 4,
	SERVICE_INTERRUPT_SUPPORTED = 5,
	RELEASE_INTERRUPT_SUPPORTED = 6,
	LOOK_AHEAD_SUPPORTED = 7,
	WRITE_CACHE_SUPPORTED = 8,
	PACKET_COMMAND_SUPPORTED = 9,
	POWER_MANAGEMENT_SET_SUPPORTED = 10,
	REMOVABLE_DEVICE_SET_SUPPORTED = 11,
	SECURITY_MODE_FEATURE_SET_SUPPORTED = 12,
	SMART_FEATURE_SET_SUPPORTED = 13,
	FLUSH_CACHE_EXT_SUPPORTED = 14,
	MANDATORY_FLUSH_CACHE_SUPPORTED = 15,
	DEVICE_CONFIG_OVERLAY_SUPPORTED = 16,
	LBA48_ENABLED = 17,
	AUTO_ACOUSTIC_MANAGEMENT_SUPPORTED = 18,
	SET_MAX_SECURITY_EXTENTSION_SUPPORTED = 19,
	POWER_UP_IN_STANDBY_SUPPORTED = 20,
	REMOVEABLE_MEDIA_STATUS_SUPPORTED = 21,
	ADVANCED_POWER_MANAGEMENT_SUPPORTED = 22,
	CFA_FEATURE_SET_SUPPORTED = 23,
	READ_WRITE_DMA_QUEUED_SUPPORTED = 24,
	DOWNLOAD_MICROCODE_SUPPORTED = 25,
	URG_WRITE_BIT_SUPPORTED = 26,
	URG_READ_BIT_SUPPORTED = 27,
	WORLD_WIDE_NAME_SUPPORTED = 28,
	WRITE_DMA_QUEUED_FUA_EXT_SUPPORTED = 29,
	WRITE_DMA_FUA_EXT_AND_WRITE_MULTIPLE_FUA_EXT = 30,
	GENERAL_PURPOSE_LOGING_SUPPORTED = 31,
	STREAMING_FEATURE_SET_SUPPORTED = 32,
	MEDIA_CARD_PASSTHROUGH_SUPPORTED = 33,
	MEDIA_SERIAL_NUMBER_SUPPORTED = 34,
	SMART_SELF_TEST_SUPPORTED = 35,
	SMART_ERROR_LOGGING_SUPPORTED = 36,
};


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
	
	//a structure representing a ATA harddrive
	typedef struct {

		//Does it exist?
		bool exists;

		//The drivetype
		enum ata_drive_type driveType;

		//Is it removable?
		bool removable;

		//Manufacturer information
		uint16_t serial_number[8];
		uint16_t firmware_revision[2];
		uint16_t model_number[20];
	
		//Iordy information
		bool iordy_supported;
		bool iordy_enabled;
	
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
		bool cmd_set_supported[36];
	
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
	
		//Misc information
		int major_ata_version;
		uint16_t minor_ata_version;
		bool pin80_connector;
		uint8_t max_queue_depth;
		uint8_t sectors_per_interrupt_rw_multiple;
		bool set_features_spinup_needed;
		
	} ata_device_t;

	//a array representing the ATA drives
	ata_device_t ata_drives[2];

	ata_device_t ata_identify(enum ata_device_select dev);

	//the main function for reading
	void sect_read_atapio(uint32_t target_address, uint64_t LBA, uint16_t sector_count, ata_device_t* dev);

	//the main function for writing
	void sect_write_atapio(uint64_t LBA, uint16_t sector_count, uint32_t* bytes, ata_device_t* dev);

	int wait_ata_bsy();

	void wait_ata_drq();
	
	void ata_error_handler();

	void ata_reset();

	void ata_standby();

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
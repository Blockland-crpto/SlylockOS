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

#if defined(__cplusplus)
extern "C" {
#endif

	//a structure representing a UDMA mode
	typedef struct {
		int id;
		bool supported;
	} udma_mode_t;


	//a structure representing a ATA harddrive
	typedef struct {

		//Does it exist?
		bool exists;

		//The drivetype
		enum ata_drive_type driveType;

		//Is it removable?
		bool removable;

		//is the controller removable?
		bool controller_removable;

		//Logical information
		uint16_t logical_sectors;
		uint16_t logical_heads;
		uint16_t logical_sectors_per_track;

		//Iordy information
		bool iordy_supported;
		bool iordy_enabled;
	
		//LBA modes
		bool lba48_enabled;
		bool lba28_enabled;

		//UDMA modes
		udma_mode_t supported_udma[7];
		udma_mode_t active_udma;

		//Misc information
		bool standby_timer_enabled;
		bool min_standby_timer_enabled;
		bool pin80_connector;
		uint8_t sectors_per_interrupt_rw_multiple;
		uint16_t serial_number[8];
		uint16_t firmware_revision[2];
		uint16_t model_number[20];
		uint32_t addressable_space_lba28;
		uint64_t addressable_space_lba48;

	} ata_device_t;

	//a array representing the ATA drives
	ata_device_t ata_drives[2];

	ata_device_t ata_identify(enum ata_device_select dev);

	//the main function for reading
	void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint16_t sector_count, ata_device_t* dev);
	//reads helper functions
	void sect_read_lba28(uint32_t LBA, uint8_t sector_count, uint32_t target_address);
	void sect_read_lba48(uint64_t LBA, uint16_t sector_count, uint32_t target_address);


	//the main function for writing
	void sect_write_atapio(uint32_t LBA, uint16_t sector_count, uint32_t* bytes, ata_device_t* dev);

	//writes helper functions
	void sect_write_lba28(uint32_t LBA, uint8_t sector_count, uint32_t* bytes);
	void sect_write_lba48(uint64_t LBA, uint16_t sector_count, uint32_t* bytes);

	int wait_ata_bsy();

	void wait_ata_drq();
	
	void ata_error_handler();

	void ata_reset();

	void ata_standby();

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
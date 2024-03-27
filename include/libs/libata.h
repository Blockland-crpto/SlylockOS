#ifndef __LIBATA_H
#define __LIBATA_H

#include <system/types.h>

//Status of the ATA Device
#define STATUS_ERR 0x01
#define STATUS_IDX 0x02
#define STATUS_CORR 0x04
#define STATUS_DRQ 0x08
#define STATUS_SRV 0x10
#define STATUS_DF 0x20
#define STATUS_RDY 0x40
#define STATUS_BSY 0x80

//ATA Error Codes
#define ERROR_AMNF 0x01
#define ERROR_TKZNF 0x02
#define ERROR_ABRT 0x04
#define ERROR_MCR 0x08
#define ERROR_IDNF 0x10
#define ERROR_MC 0x20
#define ERROR_UNC 0x40
#define ERROR_BBK 0x80

//Drive and Head Register Values
#define LBA_24_BIT 0x01
#define LBA_25_BIT 0x02
#define LBA_26_BIT 0x04
#define LBA_27_BIT 0x08
#define DAH_DRV 0x10
#define DAH_1 0x20
#define DAH_LBA 0x40
#define DAH_2 0x80

//Alternate Status Register
#define ALT_STATUS_ERR 0x01
#define ALT_STATUS_IDX 0x02
#define ALT_STATUS_CORR 0x04
#define ALT_STATUS_DRQ 0x08
#define ALT_STATUS_SRV 0x10
#define ALT_STATUS_DF 0x20
#define ALT_STATUS_RDY 0x40
#define ALT_STATUS_BSY 0x80

//Device Control Register
#define DEV_CTRL_NA1 0x01
#define DEV_CTRL_nlEN 0x02
#define DEV_CTRL_SRST 0x04
#define DEV_CTRL_NA2 0x08
#define DEV_CTRL_NA3 0x10
#define DEV_CTRL_NA4 0x20
#define DEV_CTRL_NA5 0x40
#define DEV_CTRL_HOB 0x80

//Drive Address Register
#define DRV_ADDR_DS0 0x01
#define DRV_ADDR_DS1 0x02
#define DRV_ADDR_HS0 0x04
#define DRV_ADDR_HS1 0x08
#define DRV_ADDR_HS2 0x10
#define DRV_ADDR_HS3 0x20
#define DRV_ADDR_WTG 0x40
#define DRV_ADDR_NA 0x80

//IO base and ports registers
#define IO_PORT_DATA 0x1F0
#define IO_PORT_ERROR 0x1F1
#define IO_PORT_FEATURE 0xF1
#define IO_PORT_SECTOR_COUNT 0x1F2
#define IO_PORT_SECTOR_NUMBER 0x1F3
#define IO_PORT_CYL_LOW 0x1F4
#define IO_PORT_CYL_HIGH 0x1F5
#define IO_PORT_DRIVE_HEAD 0x1F6
#define IO_PORT_STATUS 0x1F7
#define IO_PORT_COMMAND 0x1F7

//Control base and ports registers
#define CTRL_ALTERNATE_STATUS 0x3F6
#define CTRL_DEVICE 0x3F6
#define CTRL_DRIVE_ADDRESS 0x3F7

//ATA Identify Command
#define IDENTIFY_CMD 0xEC

//ATA Device Master
#define SELECT_DEVICE_MASTER 0xA0
#define SELECT_DEVICE_SLAVE 0xB0

//ATA Device Write Addresses (LBA28)
#define DEVICE_MASTER_LBA28 0xE0
#define DEVICE_SLAVE_LBA28 0xF0

//ATA Device Write Addresses (LBA48)
#define DEVICE_MASTER_LBA48 0x40
#define DEVICE_SLAVE_LBA48 0x50

//ATA drive types
#define DRIVE_TYPE_MASTER 0
#define DRIVE_TYPE_SLAVE 1

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
		int driveType;

		//LBA modes
		bool lba48_enabled;
		bool lba28_enabled;

		//UDMA modes
		udma_mode_t supported_udma[7];
		udma_mode_t active_udma;

		//Misc information
		bool pin80_connector;
		uint32_t addressable_space_lba28;
		uint64_t addressable_space_lba48;

	} ata_drive_t;

	//a array representing the ATA drives
	ata_drive_t ata_drives[2];

	ata_drive_t ata_identify(uint8_t dev);

	//the main function for reading
	void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint16_t sector_count, ata_drive_t* dev);
	//reads helper functions
	void sect_read_lba28(uint32_t LBA, uint8_t sector_count, uint32_t target_address);
	void sect_read_lba48(uint64_t LBA, uint16_t sector_count, uint32_t target_address);


	//the main function for writing
	void sect_write_atapio(uint32_t LBA, uint16_t sector_count, uint32_t* bytes, ata_drive_t* dev);

	//writes helper functions
	void sect_write_lba28(uint32_t LBA, uint8_t sector_count, uint32_t* bytes);
	void sect_write_lba48(uint64_t LBA, uint16_t sector_count, uint32_t* bytes);


	int wait_ata_bsy();

	void wait_ata_drq();

	int ata_wait_id();

	void ata_error_handler();

	void ata_reset();

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
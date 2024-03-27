#include <libata.h>
#include <libports.h>
#include <system/debug.h>
#include <system/types.h>
#include <libssp.h>

//sends the identify command to the ata device, reads it, and parses it
ata_drive_t ata_identify(uint8_t dev) {

	//creates a structure to represent a ATA drive
	ata_drive_t drive;

	//sets the drive type
	if (dev & SELECT_DEVICE_MASTER) {
		drive.driveType = DRIVE_TYPE_MASTER;
	} else {
		drive.driveType = DRIVE_TYPE_SLAVE;
	}
	
	//selects the drive as master
	outb(IO_PORT_DRIVE_HEAD, dev);

	//sets the required registers to clear
	outb(IO_PORT_SECTOR_COUNT, 0x00);
	outb(IO_PORT_SECTOR_NUMBER, 0x00);
	outb(IO_PORT_CYL_LOW, 0x00);
	outb(IO_PORT_CYL_HIGH, 0x00);

	//sends identify command
	outb(IO_PORT_COMMAND, IDENTIFY_CMD);
	
	uint8_t identify = inb(IO_PORT_STATUS);
	
	//now we parse it
	if (identify&0x00) {
		//the drive does not exist
		drive.exists == false;
		return drive;
	}
	
	int status = ata_wait_id();
	
	if (status == 1) {
		//the drive is not a valid ata drive
		drive.exists == false;
		return drive;
	} else if (status == 2) {
		//the drive errored out while running identify
		drive.exists == false;
		return drive;
	}

	//the drive is ready to be read
	uint16_t identify_data[256];
	
	for (size_t i = 0; i < 256; i++) {
		identify_data[i] = inw(IO_PORT_DATA);
	}

	//check if the ATA device is a Harddisk
	if (identify_data[0]&0x00) {
		//the drive is not a harddisk
		return;
	}

	//check if the drive supports LBA48 addressing mode
	uint16_t lba_mode = identify_data[83];
	uint16_t lba_mode_mask = 1 << 10;
	
	if (lba_mode&lba_mode_mask) {
		//the drive supports LBA48 addressing
		drive.lba48_enabled = true;
	} else {
		//the drive does not support LBA48 addressing
		drive.lba48_enabled = false;
	}
	
	//lets see the UDMA modes
	uint16_t udma_mode = identify_data[88];

	//lets see the UDMA0
	uint16_t udma_mode_mask;

	//for loop to iterate over the supported DMA's
	for (int i = 0; i < 8; i++) {
		//udma mask
		udma_mode_mask = 1 << i;
		
		if (udma_mode&udma_mode_mask) {
			//the udma mode is supported
			udma_mode_t udma;
			udma.supported = true;
			udma.id = i;
			drive.supported_udma[i] = udma;
		} else {
			//the udma mode is not supported
			udma_mode_t udma;
			udma.supported = false;
			udma.id = i;
			drive.supported_udma[i] = udma;
		}
	}

	//lets define the active bits of UDMA
	uint8_t active_udma_bits = (uint8_t)(udma_mode >> 8);

	//iterate throught the supported UDMA's
	for (int i = 0; i < 8; i++) {
		if (active_udma_bits&(1 << i)) {
			//the udma mode is being used
			drive.active_udma = drive.supported_udma[i];
		}
	}

	//lets find out if it uses a 80-pin cable
	uint16_t cable_type = identify_data[93];
	uint16_t cable_type_mask = 1 << 11;

	//it a 80-pin cable
	if (cable_type&cable_type_mask) {
		drive.pin80_connector = true;
	} else {
		drive.pin80_connector = false;
	}

	//lets find the number of 28 bit addressable space
	uint16_t addressable_space_1 = identify_data[60];
	uint16_t addressable_space_2 = identify_data[61];
	uint32_t addressable_space_lba28 = (addressable_space_2 << 8) | addressable_space_1;

	if (addressable_space_lba28&0x00) {
		drive.lba28_enabled = false;
	} else {
		drive.addressable_space_lba28 = addressable_space_lba28;
	}

	//lets find the number of 48 bit addressable space
	uint16_t addressable_space_3 = identify_data[100];
	uint16_t addressable_space_4 = identify_data[101];
	uint16_t addressable_space_5 = identify_data[102];
	uint16_t addressable_space_6 = identify_data[103];
	uint64_t addressable_space_lba48 = ((uint64_t)addressable_space_3 << 48) | ((uint64_t)addressable_space_4 << 32) | ((uint64_t)addressable_space_5 << 16) | addressable_space_6;

	if (addressable_space_lba48&0x00) {
		drive.lba48_enabled = false;
	} else {
		drive.addressable_space_lba48 = addressable_space_lba48;
	}
	drive.exists = true;
	return drive;
}
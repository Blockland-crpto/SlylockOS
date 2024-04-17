#include <libata.h>
#include <libports.h>
#include <system/debug.h>
#include <system/types.h>
#include <libssp.h>

//ATA Identify Command
#define IDENTIFY_CMD 0xEC

//Poll ATA till the status is 7
static int ata_wait_id() {
	while(inb(CTRL_ALTERNATE_STATUS)&STATUS_BSY) {
		if (inb(IO_PORT_CYL_LOW)&0x00) {
			//Not a valid ATA drive
			return 1;
		}
		if (inb(IO_PORT_CYL_HIGH)&0x00) {
			//Not a valid ATA drive
			return 1;
		}
	}
	if(inb(IO_PORT_STATUS)&STATUS_DRQ) {
		return 3;
	} else if (inb(IO_PORT_STATUS)&STATUS_ERR) {
		return 2;
	}
	return 0;
}

//sends the identify command to the ata device, reads it, and parses it
ata_device_t ata_identify(enum ata_device_select dev) {

	//creates a structure to represent a ATA drive
	ata_device_t drive;

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

	//let retrive id status
	uint8_t identify = inb(IO_PORT_STATUS);
	
	//now we parse it
	if (identify&0x00) {
		//the drive does not exist
		drive.exists = false;
		return drive;
	}

	//retrive the status of ata waiting
	int status = ata_wait_id();

	//check the status of running the id command
	if (status == 1) {
		//the drive is not a valid ata drive
		drive.exists = false;
		return drive;
	} else if (status == 2) {
		//the drive errored out while running identify
		drive.exists = false;
		return drive;
	}

	//the drive is ready to be read
	uint16_t identify_data[256];
	
	for (size_t i = 0; i < 256; i++) {
		identify_data[i] = inw(IO_PORT_DATA);
	}

	//lets get the drive configuration info
	uint16_t drive_config = identify_data[0];

	//lets have the drive type mask
	uint16_t drivetype_mask = 1 << 15;

	//lets have the removable drive mask
	uint16_t removable_mask = 1 << 7;

	//lets have the removable controller mask
	uint16_t removable_controller_mask = 0 << 6;
	
	//check if the ATA device is valid
	if (drive_config&0x00) {
		//the drive is not existent
		drive.exists = false;
		return drive;
	}
	
	//check if the drive is a hard drive
	if (drive_config&drivetype_mask) {
		//the drive is a packet device
		drive.exists = false;
		return drive;
	}

	//lets see if the drive is removable
	if (drive_config&removable_mask) {
		//the drive is removable
		drive.removable = true;
	} else {
		//the drive is not removable
		drive.removable = false;
	}

	//lets see if the drive has a removable controller
	if (drive_config&removable_controller_mask) {
		//the drive has a removable controller
		drive.controller_removable = true;
	} else {
		//the drive does not have a removable controller
		drive.controller_removable = false;
	}

	//lets get the logical sectors
	drive.logical_sectors = identify_data[1];

	//lets get the logical heads
	drive.logical_heads = identify_data[3];

	//lets get the logical sectors per track
	drive.logical_sectors_per_track = identify_data[6];

	//next lets get the serial number
	for (int i = 10; i < 19; i++) {
		//map it to serial number
		drive.serial_number[i-10] = identify_data[i];
	}

	//next lets get the firmware revision
	for (int i = 23; i < 26; i++) {
		//map it to firmware revision
		drive.firmware_revision[i-23] = identify_data[i];
	}

	//next lets get the model number
	for (int i = 27; i < 46; i++) {
		//map it to model number
		drive.model_number[i-27] = identify_data[i];
	}

	//next lets get the sectors per interrupt in read write multiple
	drive.sectors_per_interrupt_rw_multiple = (uint8_t)identify_data[47];

	//next lets see the first capabilities block
	uint16_t capabilities_one = identify_data[49];
	
	//standby timer mask
	uint16_t standby_timer_mask = 1 << 13;

	//lets check it!
	if (capabilities_one&standby_timer_mask) {
		//the drive has a standby timer
		drive.standby_timer_enabled = true;
	} else {
		//its managed by the device
		drive.standby_timer_enabled = false;
	}

	//next lets see if IORDY is supported
	//IORDY detection mask
	uint16_t iordy_detect_mask = 1 << 11;

	//lets check it!
	if (capabilities_one&iordy_detect_mask) {
		//the drive supports IORDY
		drive.iordy_supported = true;
	} else {
		//iordy is not supported
		drive.iordy_supported = false;
	}

	//now lets see if iordy is disabled
	//IORDY enabled detection mask
	uint16_t iordy_enabled_mask = 0 << 10;

	//lets check it!
	if (capabilities_one&iordy_enabled_mask) {
		//the drive has IORDY enabled
		drive.iordy_enabled = true;
	} else {
		//iordy is not enabled on the drive
		drive.iordy_enabled = false;
	}


	//next lets look at capabilities two, the only info we can get out of this is whether or not the drive has a minimum standby timer time which is at bit 0
	uint16_t capabilities_two = identify_data[50];

	//the minimum standby timer mask
	uint16_t min_standby_timer_mask = 1 << 0;

	//lets check it!
	if (capabilities_two&min_standby_timer_mask) {
		//the drive has a minimum standby timer
		drive.min_standby_timer_enabled = true;
	} else {
		//the drive does not have a minimum standby timer
		drive.min_standby_timer_enabled = false;
	}

	//next lets look at 53 to see which are valid in the next few things
	uint16_t validity_section = identify_data[53];

	//we should also define some bools to check if the drives sections are valid
	bool valid_sect_0; // is 54-58 valid?
	bool valid_sect_1; // is 64-70 valid?
	bool valid_sect_2; // is 88 valid?
	
	//54-58 validity mask
	uint16_t validity_mask = 1 << 0;

	//lets check if these are valid
	if (validity_section&validity_mask) {
		//the section is valid
		valid_sect_0 = true;
	} else {
		//the section is not valid
		valid_sect_0 = false;
	}

	//now lets check if the second section is valid
	//the new mask
	validity_mask = 1 << 1;

	//lets check it!
	if (validity_section&validity_mask) {
		//the section is valid
		valid_sect_1 = true;
	} else {
		//the section is not valid
		valid_sect_1 = false;
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

	//lets find the MDMA mode
	uint16_t mdma_mode = identify_data[63];

	//lets see the MDMA mask
	uint16_t mdma_mode_mask;

	//for loop to iterate over the supported MDMA's
	for (int i = 0; i < 3; i++) {
		//mdma mask
		mdma_mode_mask = 1 << i;

		if (mdma_mode&mdma_mode_mask) {
			//the mdma mode is supported
			mdma_mode_t mdma;
			mdma.supported = true;
			mdma.id = i;
			drive.supported_mdma[i] = mdma;
		} else {
			//the mdma mode is not supported
			mdma_mode_t mdma;
			mdma.supported = false;
			mdma.id = i;
			drive.supported_mdma[i] = mdma;
		}
	}

	//lets define the active bits of MDMA
	uint8_t active_mdma_bits = (uint8_t)(mdma_mode >> 8);

	//iterate throught the supported MDMA's
	for (int i = 8; i < 11; i++) {
		if (active_mdma_bits&(1 << i)) {
			//the udma mode is being used
			drive.active_mdma = drive.supported_mdma[i-8];
		}
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
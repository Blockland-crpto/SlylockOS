#include <libata.h>
#include <libports.h>
#include <system/types.h>
#include <libssp.h>

//helpers
extern void sect_read_lba48();
extern void sect_read_lba28();


//Read ATA
void sect_read_atapio(uint32_t target_address, uint64_t LBA, uint16_t sector_count, ata_device_t* dev) {
	int initStatus = wait_ata_bsy();

	if (initStatus == 1) {
		//todo: implement a reset
	} else if (initStatus == 2) {
		//todo: implement a drive fault handler
	}

	//lets check if its a lba48 or lba28 device
	if (dev->lba48_enabled) {
		//now lets see if its a master or slave device
		if (dev->driveType == DRIVE_TYPE_MASTER) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_MASTER_LBA48);
		} else if (dev->driveType == DRIVE_TYPE_SLAVE) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_SLAVE_LBA48);
		}
		//call the read lba48 function
		sect_read_lba48(LBA, sector_count, target_address);

	} else if (dev->lba28_enabled) {
		//now lets see if its a master or slave device
		if (dev->driveType == DRIVE_TYPE_MASTER) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_MASTER_LBA28 | ((LBA >>24) & 0xF));
		} else if (dev->driveType == DRIVE_TYPE_SLAVE) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_SLAVE_LBA28 | ((LBA >>24) & 0xF));
		}
		//call the read lba28 function
		sect_read_lba28((uint32_t)LBA, (uint8_t)sector_count, target_address);
	}	



}
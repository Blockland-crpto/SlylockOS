#include <libata.h>
#include <libports.h>
#include <system/types.h>
#include <libssp.h>

//Write ATA
void sect_write_atapio(uint32_t LBA, uint16_t sector_count, uint32_t* bytes, ata_device_t* dev) {
	wait_ata_bsy();

	//lets check if its a lba48 or lba28 device
	if (dev->lba48_enabled) {
		//now lets see if its a master or slave device
		if (dev->driveType == DRIVE_TYPE_MASTER) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_MASTER_LBA48);
		} else if (dev->driveType == DRIVE_TYPE_SLAVE) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_SLAVE_LBA48);
		}
		//call the write lba28 function
		sect_write_lba48(LBA, sector_count, bytes);
		
	} else if (dev->lba28_enabled) {
		//now lets see if its a master or slave device
		if (dev->driveType == DRIVE_TYPE_MASTER) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_MASTER_LBA28 | ((LBA >>24) & 0xF));
		} else if (dev->driveType == DRIVE_TYPE_SLAVE) {
			outb(IO_PORT_DRIVE_HEAD, DEVICE_SLAVE_LBA28 | ((LBA >>24) & 0xF));
		}
		//call the write lba28 function
		sect_write_lba28(LBA, (uint8_t)sector_count, bytes);
	}	
}
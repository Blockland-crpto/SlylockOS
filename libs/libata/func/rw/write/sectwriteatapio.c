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
//contains AbridOS code
#include <libata.h>
#include <libacpi.h>
#include <libports.h>
#include <system/types.h>
#include <libssp.h>

//the cache flush command, needed to manually flush the cache
#define CACHE_FLUSH_CMD 0xE7


//helper functions
extern void sect_write_lba48();
extern void sect_write_lba28();

//Write ATA
void sect_write_atapio(uint64_t LBA, uint16_t sector_count, uint32_t* bytes, ata_device_t* dev) {
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
		sect_write_lba28((uint32_t)LBA, (uint8_t)sector_count, bytes);
	}	

	//flush the cache
	//this needs to be done on some harddrives to prevent bad sectors
	outb(IO_PORT_COMMAND, CACHE_FLUSH_CMD);

	//lets wait
	wait_ata_bsy();

	//after were done lets check the power mode
	if (PREFERED_PM_PROFILE == 2 || PREFERED_PM_PROFILE == 8) {
		//then we need to put the device in standby mode
		ata_standby();
	}
}
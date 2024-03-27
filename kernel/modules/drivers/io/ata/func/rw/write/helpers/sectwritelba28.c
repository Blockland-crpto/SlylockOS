#include <drivers/io/ata.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <libssp.h>

void sect_write_lba28(uint32_t LBA, uint8_t sector_count, uint32_t* bytes) {
	if (inb(IO_PORT_STATUS)&STATUS_ERR) {
		//todo: implement a reset
	}
	if (inb(IO_PORT_STATUS)&STATUS_DF) {
		//todo: implement a drive fault handler
	}
	
	outb(IO_PORT_SECTOR_COUNT, sector_count);
	outb(IO_PORT_SECTOR_NUMBER, (uint8_t) LBA);
	outb(IO_PORT_CYL_LOW, (uint8_t)(LBA >> 8));
	outb(IO_PORT_CYL_HIGH, (uint8_t)(LBA >> 16)); 
	outb(IO_PORT_COMMAND, 0x30); // Send the write command!

	for (int j = 0;j<sector_count;j++) {
		wait_ata_bsy();
		wait_ata_drq();
		for(int i=0;i<256;i++) {
			outl(IO_PORT_DATA, bytes[i]);
		}
	}
}
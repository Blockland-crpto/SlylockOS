#include <libata.h>
#include <libports.h>
#include <system/types.h>
#include <libssp.h>

void sect_read_lba28(uint32_t LBA, uint8_t sector_count, uint32_t target_address) {
	outb(IO_PORT_SECTOR_COUNT, sector_count);
	outb(IO_PORT_SECTOR_NUMBER, (uint8_t) LBA);
	outb(IO_PORT_CYL_LOW, (uint8_t)(LBA >> 8));
	outb(IO_PORT_CYL_HIGH, (uint8_t)(LBA >> 16)); 
	outb(IO_PORT_COMMAND, 0x20); // Send the read command!

	uint16_t *target = (uint16_t*) target_address;

	for (int j =0;j<sector_count;j++) {
		int runningStatus = wait_ata_bsy();

		if (runningStatus == 1) {
			//todo: implement a reset
		} else if (runningStatus == 2) {
			//todo: implement a drive fault handler
		}

		wait_ata_drq();

		for(int i = 0; i < 256; i++) {
			target[i] = inw(IO_PORT_DATA);
		}

		target += 256;
	}
}
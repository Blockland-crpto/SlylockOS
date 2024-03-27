#include <drivers/io/ata.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <libssp.h>

void sect_read_lba48(uint64_t LBA, uint16_t sector_count, uint32_t target_address) {
	// Setup 48-bit LBA
	outb(IO_PORT_SECTOR_COUNT, (sector_count >> 8) & 0xFF); // High byte of sector count
	outb(IO_PORT_SECTOR_NUMBER, (LBA >> 24) & 0xFF);    // Highest bits of LBA
	outb(IO_PORT_CYL_LOW, (LBA >> 32) & 0xFF);    // Upper middle bits of LBA
	outb(IO_PORT_CYL_HIGH, (LBA >> 40) & 0xFF);   // Lower middle bits of LBA

	// Send the read command (0x24 for read)
	outb(IO_PORT_COMMAND, 0x24); // Send the read command!

	//target
	uint16_t *target = (uint16_t*) target_address;
	
	// Read Loop for 48-bit LBA
	for (int j = 0; j < sector_count; j++) {
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

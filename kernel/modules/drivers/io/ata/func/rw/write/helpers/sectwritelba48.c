#include <drivers/io/ata.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <libssp.h>

void sect_write_lba48(uint64_t LBA, uint16_t sector_count, uint32_t* bytes) {
	// Setup 48-bit LBA
	outb(IO_PORT_SECTOR_COUNT, (sector_count >> 8) & 0xFF); // High byte of sector count
	outb(IO_PORT_SECTOR_NUMBER, (LBA >> 24) & 0xFF);    // Highest bits of LBA
	outb(IO_PORT_CYL_LOW, (LBA >> 32) & 0xFF);    // Upper middle bits of LBA
	outb(IO_PORT_CYL_HIGH, (LBA >> 40) & 0xFF);   // Lower middle bits of LBA

	// Send the write command
	outb(IO_PORT_COMMAND, 0x34); // Send the write command!

	// Write Loop for 48-bit LBA
	for (int j = 0; j < sector_count; j++) {
		wait_ata_bsy();
		wait_ata_drq();
		for (int i = 0; i < 256; i++) {
			uint16_t word = bytes[j * 256 + i];
			outw(IO_PORT_DATA, word); // Write 16-bit word
		}
	}
}
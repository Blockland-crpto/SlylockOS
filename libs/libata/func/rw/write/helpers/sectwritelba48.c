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
#include <libata.h>
#include <libports.h>
#include <stdint.h>
#include <stdbool.h>
 

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
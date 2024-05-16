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
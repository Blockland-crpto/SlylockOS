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
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//function to iterate through the drives mdma support
void get_drive_udma_support(ata_device_t* drive, uint16_t* identify_data) {

	//for loop to iterate over the supported UDMA's
	for (int i = 0; i < 8; i++) {
		//lets reset the variable
		uint16_t udma_mode = identify_data[88];

		if ((udma_mode & (1 << i)) == 1) {
			//the udma mode is supported
			udma_mode_t udma;
			udma.supported = true;
			udma.id = i;
			drive->supported_udma[i] = udma;
		} else {
			//the udma mode is not supported
			udma_mode_t udma;
			udma.supported = false;
			udma.id = i;
			drive->supported_udma[i] = udma;
		}

		udma_mode = identify_data[88];
		
		//lets define the active bits of UDMA
		uint8_t active_udma_bits = (uint8_t)(udma_mode >> 8);

		if ((active_udma_bits & (1 << i)) == 1) {
			//the udma mode is being used
			drive->active_udma = drive->supported_udma[i];
		}
	}
}
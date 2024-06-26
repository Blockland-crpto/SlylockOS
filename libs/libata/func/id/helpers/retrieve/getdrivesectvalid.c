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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

//function to retreive info from valid dependent area 1
void get_drive_sect_valid(ata_device_t* drive, uint16_t* identify_data) {
	//validate
	if (drive == NULL || identify_data == NULL) {
		//oops!
		return;
	}

	//iterate through supported pio modes
	for (int i = 0; i < 8; i++) {
		//lets reset the variable
		uint16_t pio_mode = identify_data[64];
		
		//lets check it!
		drive->supported_pio[i].supported = enabled(i, pio_mode);
		drive->supported_pio[i].id = i;
	}

	//lets get the minimum mdma transfer per word
	drive->min_mdma_transfer_time_per_word = identify_data[65];

	//lets get the manufactures recommended min mda transfer time
	drive->min_mdma_transfer_time_vendor = identify_data[66];

	//lets get the minimum pio transfer time without flow control
	drive->min_pio_transfer_time_no_flow_ctrl = identify_data[67];

	//lets get the minimum pio transfer time with flow control
	drive->min_pio_transfer_time_iordy_flow_ctrl = identify_data[68];
}
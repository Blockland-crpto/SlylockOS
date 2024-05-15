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
 
#include <stddef.h>

//function to iterate through the drives mdma support
void get_drive_mdma_support(ata_device_t* drive, uint16_t* identify_data) {

	//input validate
	if (drive == NULL || identify_data == NULL) {
		//oops!
		return;
	}
	
	//for loop to iterate over the supported MDMA's
	for (int i = 0; i < 3; i++) {

		//lets reset the variable
		uint16_t mdma_mode = identify_data[63];

		if ((mdma_mode & (1 << i)) == 1) {
			//the mdma mode is supported
			mdma_mode_t mdma;
			mdma.supported = true;
			mdma.id = i;
			drive->supported_mdma[i] = mdma;
		} else {
			//the mdma mode is not supported
			mdma_mode_t mdma;
			mdma.supported = false;
			mdma.id = i;
			drive->supported_mdma[i] = mdma;
		}

		//lets reset the variable
		mdma_mode = identify_data[63];
		
		uint8_t active_mdma_bits = (uint8_t)(mdma_mode >> 8);

		if ((active_mdma_bits & (1 << i)) == 1) {
			//the udma mode is being used
			drive->active_mdma = drive->supported_mdma[i];
		}
	}
}
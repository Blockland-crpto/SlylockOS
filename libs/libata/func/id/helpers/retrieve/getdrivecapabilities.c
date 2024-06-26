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
#include <cmdset.h>

//function to get drive capabilities
void get_drive_capabilities(ata_device_t* drive, uint16_t* identify_data) {

	//validate
	if (drive == NULL || identify_data == NULL) {
		//oops!
		return;
	}

	//lets have a compare variable
	uint16_t compare = identify_data[49];

	//for loop to iterate through common functions
	for (int i = 11; i >= 8; i--) {
		//lets reset the compare variable
		compare = identify_data[49];

		//lets switch i
		switch(i) {
			case 11: {
				//lets see if iordy is avalible
				drive->iordy_data.iordy_supported = enabled(i, compare);
				break;
			}
			case 10: {
				//is it disabled?
				drive->iordy_data.iordy_disabled = enabled(i, compare);
				break;
			}
			case 8: {
				//is dma supported?
				drive->dma_supported = enabled(i, compare);
				break;
			}
			default: {
				break;
			}
		}
	}
	
	//lets make compare capabilites two
	compare = identify_data[50];

	//is there a minimum standby
	drive->standby_timer_data.min_standby_timer_enabled = enabled(0, compare);

	//lets first see the ATAPI stuff
	if (drive->atapi_info.is_atapi) {
		//lets iterate over it
		for (int i = 15; i >= 8; i--) {
			//lets reset to compare variable
			compare = identify_data[49];

			//switch!
			switch (i) {
				case 15: {
					//is interleaved dma supported?
					drive->atapi_info.feature_set_supported[INTERLEAVED_DMA_SUPPORTED].supported = enabled(i, compare);
					break;
				}
				case 14: {
					//is command queueing supported?
					drive->atapi_info.feature_set_supported[COMMAND_QUEUEING_SUPPORTED].supported = enabled(i, compare);
					break;
				}
				case 13: {
					//is overlap operation supported?
					drive->atapi_info.feature_set_supported[OVERLAP_OPERATION_SUPPORTED].supported = enabled(i, compare);
					break;
				}
				default: {
					break;
				}
				//todo: add vendor specific information
			}
		}
		
	} else {
		//its a normal device lets see it!
		//for loop to iterate!
		for (int i = 13; i > 8; i--) {
			//lets reset to compare variable
			compare = identify_data[49];

			//lets switch
			switch(i) {
				case 13: {
					drive->standby_timer_data.standby_timer_enabled = enabled(i, compare);
					break;
				}
				case 9: {
					drive->lba_data.lba_supported = enabled(i, compare);
					break;
				}
				default: {
					break;
				}
			}
		}
	}
}
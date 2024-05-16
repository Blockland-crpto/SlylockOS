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
 

//function to get drive capabilities
void get_drive_capabilities(ata_device_t* drive, uint16_t* identify_data) {
	//next lets see the capabilities blocks
	uint16_t capabilities_one = identify_data[49];
	uint16_t capabilities_two = identify_data[50];

	//lets have a compare variable
	uint16_t compare;

	//for loop to iterate through common functions
	for (int i = 11; i >= 8; i--) {
		//lets reset the compare variable
		compare = capabilities_one;

		//lets switch i
		switch(i) {
			case 11: {
				//lets see if iordy is avalible
				drive->iordy_supported = (compare & (1 << i)) ? true : false;
				break;
			}
			case 10: {
				//is it disabled?
				drive->iordy_disabled =  (compare & (1 << i)) ? true : false;
				break;
			}
			case 8: {
				//is dma supported?
				drive->dma_supported = (compare & (1 << i)) ? true : false;
				break;
			}
			default: {
				break;
			}
		}
	}
	
	//lets make compare capabilites two
	compare = capabilities_two;

	//is there a minimum standby
	drive->min_standby_timer_enabled = (capabilities_two & (1 << 0)) ? true : false;

	//lets first see the ATAPI stuff
	if (drive->atapi_info.is_atapi) {
		//lets iterate over it
		for (int i = 15; i >= 8; i--) {
			//lets reset to compare variable
			compare = capabilities_one;
			
			//lets see if its supported
			bool supported = (compare & (1 << i)) ? true : false;

			//switch!
			switch (i) {
				case 15: {
					//is interleaved dma supported?
					drive->atapi_info.feature_set_supported[INTERLEAVED_DMA_SUPPORTED].supported = supported;
					break;
				}
				case 14: {
					//is command queueing supported?
					drive->atapi_info.feature_set_supported[COMMAND_QUEUEING_SUPPORTED].supported = supported;
					break;
				}
				case 13: {
					//is overlap operation supported?
					drive->atapi_info.feature_set_supported[OVERLAP_OPERATION_SUPPORTED].supported = supported;
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
			compare = capabilities_one;
			
			//lets see if its supported
			bool supported = (compare & (1 << i)) ? true : false;

			//lets switch
			switch(i) {
				case 13: {
					drive->standby_timer_enabled = supported;
					break;
				}
				case 9: {
					drive->lba_supported = supported;
					break;
				}
				default: {
					break;
				}
			}
		}
	}
}
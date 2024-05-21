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

#ifndef __CMDSET_H
#define __CMDSET_H

#include <stdbool.h>

#define enabled(i, cse) ((cse & (1 << i)) ? true : false)

//ATA supported array key
enum ata_supported_array_key {
	NOP_SUPPORTED = 0,
	READ_BUFFER_SUPPORTED = 1,
	WRITE_BUFFER_SUPPORTED = 2,
	HOST_PROTECTED_AREA_SUPPORTED = 3,
	DEVICE_RESET_SUPPORTED = 4,
	SERVICE_INTERRUPT_SUPPORTED = 5,
	RELEASE_INTERRUPT_SUPPORTED = 6,
	LOOK_AHEAD_SUPPORTED = 7,
	WRITE_CACHE_SUPPORTED = 8,
	PACKET_COMMAND_SUPPORTED = 9,
	POWER_MANAGEMENT_SET_SUPPORTED = 10,
	REMOVABLE_DEVICE_SET_SUPPORTED = 11,
	SECURITY_MODE_FEATURE_SET_SUPPORTED = 12,
	SMART_FEATURE_SET_SUPPORTED = 13,
	FLUSH_CACHE_EXT_SUPPORTED = 14,
	MANDATORY_FLUSH_CACHE_SUPPORTED = 15,
	DEVICE_CONFIG_OVERLAY_SUPPORTED = 16,
	LBA48_ENABLED = 17,
	AUTO_ACOUSTIC_MANAGEMENT_SUPPORTED = 18,
	SET_MAX_SECURITY_EXTENTSION_SUPPORTED = 19,
	POWER_UP_IN_STANDBY_SUPPORTED = 20,
	REMOVEABLE_MEDIA_STATUS_SUPPORTED = 21,
	ADVANCED_POWER_MANAGEMENT_SUPPORTED = 22,
	CFA_FEATURE_SET_SUPPORTED = 23,
	READ_WRITE_DMA_QUEUED_SUPPORTED = 24,
	DOWNLOAD_MICROCODE_SUPPORTED = 25,
	URG_WRITE_BIT_SUPPORTED = 26,
	URG_READ_BIT_SUPPORTED = 27,
	WORLD_WIDE_NAME_SUPPORTED = 28,
	WRITE_DMA_QUEUED_FUA_EXT_SUPPORTED = 29,
	WRITE_DMA_FUA_EXT_AND_WRITE_MULTIPLE_FUA_EXT = 30,
	GENERAL_PURPOSE_LOGING_SUPPORTED = 31,
	STREAMING_FEATURE_SET_SUPPORTED = 32,
	MEDIA_CARD_PASSTHROUGH_SUPPORTED = 33,
	MEDIA_SERIAL_NUMBER_SUPPORTED = 34,
	SMART_SELF_TEST_SUPPORTED = 35,
	SMART_ERROR_LOGGING_SUPPORTED = 36,
};

//ATAPI supported array key
enum atapi_supported_array_key {
	INTERLEAVED_DMA_SUPPORTED = 0,
	COMMAND_QUEUEING_SUPPORTED = 1,
	OVERLAP_OPERATION_SUPPORTED = 2,
	
};

#if defined(__cplusplus)
extern "C" {
#endif

	//a sturcture representing a command set feature
	typedef struct {
		bool enabled :1;
		bool supported :1;
	} cmd_set_t;

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
#include <libata.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//function to get the drive cmd set 2
void get_drive_cmd_set_ext(ata_device_t* drive, uint16_t* identify_data) {
	
	//for loop to iterate through the word
	for (int i = 10; i >= 0; i--) {

		//lets reset the compare variable
		uint16_t command_sets_ext = identify_data[84];
		
		//supported bool
		bool supported = (command_sets_ext & (1 << i));

		//switched the mask
		switch(i) {
			case 10: {
				//is the URG bit supported for WRITE STREAM DMA or PIO
				drive->cmd_set_supported[URG_WRITE_BIT_SUPPORTED].supported = supported;
				break;
			}
			case 9: {
				//is the URG bit supported for READ STREAM DMA or PIO
				drive->cmd_set_supported[URG_READ_BIT_SUPPORTED].supported = supported;
				break;
			}
			case 8: {
				//is world wide name supported?
				drive->cmd_set_supported[WORLD_WIDE_NAME_SUPPORTED].supported = supported;
				break;
			}
			case 7: {
				//is WRITE DMA QUEUED FUA EXT command supported 
				drive->cmd_set_supported[WRITE_DMA_QUEUED_FUA_EXT_SUPPORTED].supported = supported;
				break;
			}
			case 6: {
				//is WRITE DMA FUA EXT and WRITE MULTIPLE FUA EXT commands supported?
				drive->cmd_set_supported[WRITE_DMA_FUA_EXT_AND_WRITE_MULTIPLE_FUA_EXT].supported = supported;
				break;
			}
			case 5: {
				//is the general purpose logging feature set supported?
				drive->cmd_set_supported[GENERAL_PURPOSE_LOGING_SUPPORTED].supported = supported;
				break;
			}
			case 4: {
				//is the streaming feature set supported?
				drive->cmd_set_supported[STREAMING_FEATURE_SET_SUPPORTED].supported = supported;
				break;
			}
			case 3: {
				//is media card pass through supported?
				drive->cmd_set_supported[MEDIA_CARD_PASSTHROUGH_SUPPORTED].supported = supported;
				break;
			}
			case 2: {
				//is media serial number supported?
				drive->cmd_set_supported[MEDIA_SERIAL_NUMBER_SUPPORTED].supported = supported;
				break;
			}
			case 1: {
				//is SMART self test supported?
				drive->cmd_set_supported[SMART_SELF_TEST_SUPPORTED].supported = supported;
				break;
			}
			case 0: {
				//is SMART error logging supported?
				drive->cmd_set_supported[SMART_ERROR_LOGGING_SUPPORTED].supported = supported;
				break;
			}
			default: {
				//should error out
				break;
			}
		}
	}
}
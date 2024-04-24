#include <libata.h>
#include <cmdset.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//function to get the drive cmd set 2
void get_drive_cmd_set_enabled_2(ata_device_t* drive, uint16_t* identify_data) {


	//for loop to iterate through the word
	for (int i = 9; i >= 0; i--) {

		//lets reset the compare variable
		uint16_t command_sets_enabled = identify_data[86];
		
		//enabled bool
		bool enabled = (command_sets_enabled & (1 << i)) ? true : false;

		//switched the mask
		switch(i) {
			case 9: {
				//is automatic acoustic management enabled
				drive->cmd_set_supported[AUTO_ACOUSTIC_MANAGEMENT_SUPPORTED].enabled = enabled;
				break;
			}
			case 8: {
				//is set max security extentsion enabled
				drive->cmd_set_supported[SET_MAX_SECURITY_EXTENTSION_SUPPORTED].enabled = enabled;
				break;
			}
			case 5: {
				//is power up in standby enabled
				drive->cmd_set_supported[POWER_UP_IN_STANDBY_SUPPORTED].enabled = enabled;
				break;
			}
			case 4: {
				//is removable set enabled
				drive->cmd_set_supported[REMOVEABLE_MEDIA_STATUS_SUPPORTED].enabled = enabled;
			}
			case 3: {
				//is the power management set enabled
				drive->cmd_set_supported[ADVANCED_POWER_MANAGEMENT_SUPPORTED].enabled = enabled;
				break;
			}
			case 2: {
				//is CFA enabled
				drive->cmd_set_supported[CFA_FEATURE_SET_SUPPORTED].enabled = enabled;
				break;
			}
			case 1: {
				//is R/W DMA Queued enabled
				drive->cmd_set_supported[READ_WRITE_DMA_QUEUED_SUPPORTED].enabled = enabled;
				break;
			}
			case 0: {
				//is download microcode enabled
				drive->cmd_set_supported[DOWNLOAD_MICROCODE_SUPPORTED].enabled = enabled;
				break;
			}
			default: {
				//not anything
				break;
			}
		}
	}

}
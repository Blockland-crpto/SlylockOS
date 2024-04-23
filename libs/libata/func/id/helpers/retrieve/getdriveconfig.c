#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>


//function to retrieve config info
void get_drive_config(ata_device_t* drive, uint16_t drive_config) {
	//compare variable
	uint16_t compare = drive_config;
	
	//check if the ATA device is valid
	if ((compare & 0x00) == 1) {
		//the drive is a ATAPI device
		drive->exists = false;
		return;
	}

	//lets reset it
	compare = drive_config;
	
	//is the device a ATAPI device?
	if (!drive->atapi_info.is_atapi) {
		//check if the drive is a hard drive
		if ((compare & (1 << 15)) == 1) {
			//the drive is a packet device
			drive->exists = false;
			return;
		}
	}

	//lets reset the variable
	compare = drive_config;

	//lets see if the drive is removable (its common between ATA and ATAPI devices)
	drive->removable = (compare & (1 << 7)) ? true : false;


	//lets reset it!
	compare = drive_config;
	
	//need to check if its a ATAPI device
	//lets see the byte packet information
	if (drive->atapi_info.is_atapi) {
		//lets see the byte packet information
		if ((compare & (1 << 0)) == 1) {
			//the drive has a 16 byte cmd packet
			drive->atapi_info.atapi_cmd_packet_size = ATAPI_CMD_BYTE_16BYTES;
		}

		//lets reset the variable
		compare = drive_config;
		
		//lets see if it will set DRQ within recieveing packet command
		if ((compare & (0 << 6)) == 1) {
			//sets within 3 ms of recieving packet command
			drive->atapi_info.atapi_drq_set_times = DRQ_SET_TIMES_3MS;
		} else {
			//send within 50 micro seconds
			drive->atapi_info.atapi_drq_set_times = DRQ_SET_TIMES_50MICROS;
		}
	}

	//return!
	return;
}
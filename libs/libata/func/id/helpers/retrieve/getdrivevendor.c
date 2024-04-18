#include <libata.h>
#include <libports.h>
#include <system/debug.h>
#include <system/types.h>
#include <libssp.h>


//function to retrieve vendor info
void get_drive_vendor(ata_device_t* drive, uint16_t* identify_data) {
	//next lets get the serial number
	for (int i = 10; i < 19; i++) {
		//map it to serial number
		drive->serial_number[i-10] = identify_data[i];
	}

	//next lets get the firmware revision
	for (int i = 23; i < 26; i++) {
		//map it to firmware revision
		drive->firmware_revision[i-23] = identify_data[i];
	}

	//next lets get the model number
	for (int i = 27; i < 46; i++) {
		//map it to model number
		drive->model_number[i-27] = identify_data[i];
	}
}
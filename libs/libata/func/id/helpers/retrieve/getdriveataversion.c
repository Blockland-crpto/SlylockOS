#include <libata.h>
#include <libports.h>
#include <system/debug.h>
#include <system/types.h>
#include <libssp.h>


//get the drives ata version
void get_drive_ata_version(ata_device_t* drive, uint16_t* identify_data) {
	//lets now get the major version supported number
	uint16_t major_version = identify_data[80];

	//int representing the major version
	int major_version_int = 3;

	//iterate until we find unsupported
	for (int i = 7; i > 2; i--) {
		//the mask
		uint16_t major_version_mask = 1 << i;

		//lets check it!
		if (!(major_version & major_version_mask)) {
			//nope
		} else {
			//it is supported
			major_version_int++;
		}
	}
	
	//input it to our drive!
	drive->major_ata_version = major_version_int;

	//lets now get the minor version
	drive->minor_ata_version = identify_data[81];

	//return
	return;
}
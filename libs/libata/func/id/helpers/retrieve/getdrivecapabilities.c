#include <libata.h>
#include <libports.h>
#include <system/debug.h>
#include <system/types.h>
#include <libssp.h>

//function to get drive capabilities
void get_drive_capabilities(ata_device_t* drive, uint16_t* identify_data) {
	//next lets see the first capabilities block
	uint16_t capabilities_one = identify_data[49];

	//standby timer mask
	uint16_t standby_timer_mask = 1 << 13;

	//lets check it!
	if (capabilities_one&standby_timer_mask) {
		//the drive has a standby timer
		drive->standby_timer_enabled = true;
	} else {
		//its managed by the device
		drive->standby_timer_enabled = false;
	}

	//next lets see if IORDY is supported
	//IORDY detection mask
	uint16_t iordy_detect_mask = 1 << 11;

	//lets check it!
	if (capabilities_one&iordy_detect_mask) {
		//the drive supports IORDY
		drive->iordy_supported = true;
	} else {
		//iordy is not supported
		drive->iordy_supported = false;
	}

	//now lets see if iordy is disabled
	//IORDY enabled detection mask
	uint16_t iordy_enabled_mask = 0 << 10;

	//lets check it!
	if (capabilities_one&iordy_enabled_mask) {
		//the drive has IORDY enabled
		drive->iordy_enabled = true;
	} else {
		//iordy is not enabled on the drive
		drive->iordy_enabled = false;
	}

	//now lets see if LBA is supported
	//LBA detection mask
	uint16_t lba_detect_mask = 1 << 9;

	//lets check it!
	if (capabilities_one&lba_detect_mask) {
		//the drive supports LBA
		drive->lba_supported = true;
	} else {
		//lba is not supported
		drive->lba_supported = false;
	}

	//now lets see if DMA is supported
	//DMA detection mask
	uint16_t dma_detect_mask = 1 << 8;

	//lets check it!
	if (capabilities_one&dma_detect_mask) {
		//the drive supports DMA
		drive->dma_supported = true;
	} else {
		//dma is not supported
		drive->dma_supported = false;
	}

	//next lets look at capabilities two, the only info we can get out of this is whether or not the drive has a minimum standby timer time which is at bit 0
	uint16_t capabilities_two = identify_data[50];

	//the minimum standby timer mask
	uint16_t min_standby_timer_mask = 1 << 0;

	//lets check it!
	if (capabilities_two&min_standby_timer_mask) {
		//the drive has a minimum standby timer
		drive->min_standby_timer_enabled = true;
	} else {
		//the drive does not have a minimum standby timer
		drive->min_standby_timer_enabled = false;
	}
}
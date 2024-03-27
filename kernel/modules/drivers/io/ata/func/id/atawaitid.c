#include <drivers/io/ata.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <libssp.h>

//Poll ATA till the status is 7
int ata_wait_id() {
	while(inb(CTRL_ALTERNATE_STATUS)&STATUS_BSY) {
		if (inb(IO_PORT_CYL_LOW)&0x00) {
			//Not a valid ATA drive
			return 1;
		}
		if (inb(IO_PORT_CYL_HIGH)&0x00) {
			//Not a valid ATA drive
			return 1;
		}
	}
	if(inb(IO_PORT_STATUS)&STATUS_DRQ) {
		return 3;
	} else if (inb(IO_PORT_STATUS)&STATUS_ERR) {
		return 2;
	}
	return 0;
}
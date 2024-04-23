#include <libata.h>
#include <libports.h>
#include <libdebug.h>
#include <system/types.h>
#include <libssp.h>

//Poll ATA till the status is 7
int wait_ata_id() {
	while((inb(CTRL_ALTERNATE_STATUS) & STATUS_BSY) == 1) {
		if ((inb(IO_PORT_CYL_LOW) & 0x00) == 1) {
			//Not a valid ATA drive
			return 1;
		}
		if ((inb(IO_PORT_CYL_HIGH) & 0x00) == 1) {
			//Not a valid ATA drive
			return 1;
		}
	}
	if((inb(IO_PORT_STATUS) & STATUS_DRQ) == 1) {
		return 3;
	} else if ((inb(IO_PORT_STATUS) & STATUS_ERR) == 1) {
		return 2;
	}
	return 0;
}
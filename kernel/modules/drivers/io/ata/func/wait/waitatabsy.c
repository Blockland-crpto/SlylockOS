#include <drivers/io/ata.h>
#include <drivers/io/ports.h>
#include <system/types.h>
#include <libssp.h>

//Wait for ATA
int wait_ata_bsy() {
	while(inb(CTRL_ALTERNATE_STATUS)&STATUS_BSY) {
		//check if the error bit is set
		if (inb(CTRL_ALTERNATE_STATUS)&STATUS_ERR) {
			return 1;
		} else if (inb(CTRL_ALTERNATE_STATUS)&STATUS_DF) {
			return 2;
		}
	}
	return 0;
}
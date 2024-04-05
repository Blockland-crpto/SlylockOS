#include <libata.h>
#include <libports.h>
#include <system/types.h>
#include <libssp.h>

//Wait till ready
void wait_ata_drq() {
	while(!(inb(IO_PORT_STATUS)&STATUS_RDY));
}
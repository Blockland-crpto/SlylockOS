#include <libata.h>
#include <libports.h>
#include <system/types.h>
#include <system/modules.h>
#include <libssp.h>

//ATA initializer
void ata_init() {
	module_t modules_ata = MODULE("kernel.modules.ata", "Provides ATA support for the kernel, read/write (CORE)");
	INIT(modules_ata);
	ata_device_t master = ata_identify(SELECT_DEVICE_MASTER);
	ata_device_t slave = ata_identify(SELECT_DEVICE_SLAVE);
	if (master.exists == false) {
		FAIL(modules_ata, "Master ATA drive does not exist");
	} else {
		ata_drives[0] = master;
		DONE(modules_ata);
	}
	
}
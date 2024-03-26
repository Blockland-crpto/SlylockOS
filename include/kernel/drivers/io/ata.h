#ifndef __DRIVERS_IO_ATA_H
#define __DRIVERS_IO_ATA_H

#include <system/types.h>

#define STATUS_BSY 0x80
#define STATUS_RDY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01

#if defined(__cplusplus)
extern "C" {
#endif

	void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint8_t sector_count);

	void sect_write_atapio(uint32_t LBA, uint8_t sector_count, uint32_t* bytes);

	void wait_ata_bsy();

	void wait_ata_drq();

#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
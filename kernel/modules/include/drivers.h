/**
  \file      drivers.h
  \brief     drivers
  \details   This header file is used as an ATA driver.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/
 

#ifndef __DRIVERS_H

#define __DRIVERS_H

#include <types.h>
#include <stdint.h>
#include <stddef.h>
#include <screen.h>

/**
  \def STATUS_BSY
  \brief Busy status for ATA

  Defines the busy status for the ATA driver with hex 0x80.
*/
#define STATUS_BSY 0x80
/**
  \def STATUS_RDY
  \brief Ready status for ATA
  
  Defines the ready status for the ATA driver with hex 0x40.
*/
#define STATUS_RDY 0x40
/**
  \def STATUS_DRQ
  \brief Data transfer requested status for ATA
  
  Defines the "data transfer requested" status for the ATA driver with hex 0x08.
*/
#define STATUS_DRQ 0x08
/**
  \def STATUS_DF
  \brief Device fault status for ATA
  
  Defines the device fault status for the ATA driver with hex 0x20.
*/
#define STATUS_DF 0x20
/**
  \def STATUS_ERR
  \brief Device error status for ATA
  
  Defines the error status for the ATA driver with hex 0x01.
*/
#define STATUS_ERR 0x01

/** 
   \brief Reads a sector from the hard drive

   Reads sector_count*512 bytes from the hard drive in ATA PIO mode.
   \param{out} target_address The target to modify when the function is finished. When the function is done running, `target` will have all 512 bytes in it.
   \param{in} LBA The amount of sectors to offset the read by (0x0 = first sector, 0x1 = second sector, etc.)
   \param{in} sector_count The amount of sectors in total to read. The sectors read are equal to {LBA<x<LBA+sector_count}
*/
void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint8_t sector_count);
/** 
   \brief Writes a sector to the hard drive

   Writes sector_count*512 bytes from the hard drive in ATA PIO mode.
   \param{in} LBA The amount of sectors to offset the read by (0x0 = first sector, 0x1 = second sector, etc.)
   \param{in} sector_count The amount of sectors in total to read. The sectors read are equal to {LBA<x<LBA+sector_count}
   \param{in} bytes The bytes to write to the sector(s).
*/
void sect_write_atapio(uint32_t LBA, uint8_t sector_count, uint32_t* bytes);

/**
	\brief Waits until the hard drive is not busy

	Contains a while() loop that waits until the hard drive is no longer busy.
*/
static void wait_ata_bsy();
/**
	\brief Waits until the hard drive is requesting data

	Contains a while() loop that waits until the hard drive is requesting data.
*/
static void wait_ata_drq();







/** THE VIDEO DRIVER **/

enum video_type {
	VIDEO_TYPE_NONE = 0x00,
	VIDEO_TYPE_COLOR = 0x20,
	VIDEO_TYPE_MONOCHROME = 0x30,
};

uint16_t detect_bios_area_hardware();
enum video_type get_bios_area_video_type();







/** THE ACPI DRIVER **/
dword *SMI_CMD;
byte ACPI_ENABLE;
byte ACPI_DISABLE;
dword *PM1a_CNT;
dword *PM1b_CNT;
word SLP_TYPa;
word SLP_TYPb;
word SLP_EN;
word SCI_EN;
byte PM1_CNT_LEN;

struct RSDPtr
{
   byte Signature[8];
   byte CheckSum;
   byte OemID[6];
   byte Revision;
   dword *RsdtAddress;
};

struct FACP
{
   byte Signature[4];
   dword Length;
   byte unneded1[40 - 8];
   dword *DSDT;
   byte unneded2[48 - 44];
   dword *SMI_CMD;
   byte ACPI_ENABLE;
   byte ACPI_DISABLE;
   byte unneded3[64 - 54];
   dword *PM1a_CNT_BLK;
   dword *PM1b_CNT_BLK;
   byte unneded4[89 - 72];
   byte PM1_CNT_LEN;
};

unsigned int *acpiCheckRSDPtr(unsigned int *ptr);

unsigned int *acpiGetRSDPtr(void);

int acpiCheckHeader(unsigned int *ptr, char *sig);

int acpiEnable(void);

int initAcpi(void);

void acpiPowerOff(void);

void acpi_init();

int acpiEnabled;

#endif
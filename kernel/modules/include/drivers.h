/**
  \file      drivers.h
  \brief     drivers
  \details   This header file is used as a general compilations of the drivers
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

/** ATA DRIVER START **/

/** ATA DRIVER END **/



/** VIDEO DRIVER START **/
enum video_type {
	VIDEO_TYPE_NONE = 0x00,
	VIDEO_TYPE_COLOR = 0x20,
	VIDEO_TYPE_MONOCHROME = 0x30,
};
uint16_t detect_bios_area_hardware();
enum video_type get_bios_area_video_type();
void video_init();
/** VIDEO DRIVER END **/



/** ACPI DRIVER START **/
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
struct RSDPtr {
   byte Signature[8];
   byte CheckSum;
   byte OemID[6];
   byte Revision;
   dword *RsdtAddress;
};
struct FACP {
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
/** ACPI DRIVER END **/



/** MMIO DRIVER START **/
uint8_t mmioRead8 (uint64_t p_address);
uint16_t mmioRead16 (uint64_t p_address);
uint32_t mmioRead32 (uint64_t p_address);
uint64_t mmioRead64 (uint64_t p_address);
void mmioWrite8 (uint64_t p_address,uint8_t p_value);
void mmioWrite16 (uint64_t p_address,uint16_t p_value);
void mmioWrite32 (uint64_t p_address,uint32_t p_value);
void mmioWrite64 (uint64_t p_address,uint64_t p_value);
/** MMIO DRIVER END **/



/** KEYBOARD DRIVER START **/

/** KEYBOARD DRIVER END **/
#endif
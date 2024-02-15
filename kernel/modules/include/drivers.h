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

/** ACPI DRIVER START **/

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
/**
  \file      debug.h
  \brief     Provides kernel debugging facilities
  \details   Allows the kernel to kernel panic, with reasonable amounts of details and a log.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/


#ifndef __SYSTEM_DEBUG_H
#define __SYSTEM_DEBUG_H

/**
	\def INSUFFICIENT_RAM
	\brief Insufficient RAM error code
*/
#define INSUFFICIENT_RAM 1
/**
	\def UNKNOWN
	\brief Unknwon error error code
*/
#define UNKNOWN 2
/**
	\def MEMORY_MAP_INVALID
	\brief GRUB memory map is invalid

	If the GRUB memory map is invalid, something is wrong with GRUB. Please update GRUB or report an issue to our GitHub.
*/
#define MEMORY_MAP_INVALID 3
/**
	\def USER_CREATED_PANIC
	\brief Happens if the user creates a panic with the `panic` command
*/
#define USER_CREATED_PANIC 4
/**
	\def ACPI_ERROR
	\brief Happens if the ACPI driver fails to initialize
*/
#define ACPI_ERROR 5
/**
	\def ACPI_DSDT_ERROR
	\brief Happens if the PCI driver fails to initialize because the DSDT table is invalid
*/
#define ACPI_DSDT_ERROR 6
/**
	\def VIDEO_RETRIV_ERROR
	\brief Happens if the video driver fails to retrive video data
*/
#define VIDEO_RETRIV_ERROR 7
/**
 	\def APP_ERROR
	\brief Happens if the application calls panic
*/
#define APP_ERROR 8
/**
	\def TASK_ERROR
	\brief Happens if a kernel process dies
*/
#define TASK_ERROR 9

void panic(char* reason, int errno);

//warn function
void warn(char* reason);
#endif
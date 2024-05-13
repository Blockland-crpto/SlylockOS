/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
/**
  \file      debug.h
  \brief     Provides kernel debugging facilities
  \details   Allows the kernel to kernel panic, with reasonable amounts of details and a log.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/


#ifndef __LIBDEBUG_H
#define __LIBDEBUG_H

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
	\def SSP_ERROR
	\brief Happens if stack smashing protector is tripped
*/
#define SSP_ERROR 9
/**
	\def SSP_LOCAL_ERROR
	\brief Happens if stack smashing protector is tripped locally
*/
#define SSP_LOCAL_ERROR 10
/**
	\def TASK_MAX
	\brief Happens if more then maximum tasks are attempted to be created
*/
#define TASK_MAX 11
/**
	\def DELEGATE_ERROR
	\brief Happens if the delegate errors for some reason
*/
#define DELEGATE_ERROR 12
/**
	\def DEVMGR_ERROR
	\brief Happens if the devmgr errors for some reason
*/
#define DEVMGR_ERROR 13

#if defined(__cplusplus)
extern "C" {
#endif

	//panic function
	__attribute__((noreturn)) void panic(char* reason, int errno);

	//warn function
	void warn(char* reason);

	//function to log to serial
	int slog(const char *format, ...);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
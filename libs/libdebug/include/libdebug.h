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

enum error_codes {
	INSUFFICIENT_RAM = 1,
	UNKNOWN = 2,
	MEMORY_MAP_INVALID = 3,
	USER_CREATED_PANIC = 4,
	ACPI_ERROR = 5,
	ACPI_DSDT_ERROR = 6,
	VIDEO_RETRIV_ERROR = 7,
	APP_ERROR = 8,
	SSP_ERROR = 9,
 	SSP_LOCAL_ERROR = 10,
	TASK_MAX = 11,
	DELEGATE_ERROR = 12,
	DEVMGR_ERROR = 13,
	INT_ERROR = 14,
	PROC_RET_INVALID = 15,
};

#if defined(__cplusplus)
extern "C" {
#endif

	//panic function
	__attribute__((noreturn)) void panic(char* reason, enum error_codes errno);

	//warn function
	void warn(char* reason);

	//function to log to serial
	int slog(const char *format, ...);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
/**
  \file      multibootinfo.h
  \brief     Multiboot info, obtained from the kernel main function
  \details   This header file is used in files except main.c to get multiboot info.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#include <system/mltb/multiboot.h>

#ifndef __SYSTEM_MLTB_MULTIBOOTINFO_H
#define __SYSTEM_MLTB_MULTIBOOTINFO_H

#if defined(__cplusplus)
extern "C" {
#endif
	multiboot_info_t* mbi;
#if defined(__cplusplus)
} /* extern "C" */
#endif

	

#endif
/**
  \file      gdt.h
  \brief     GDT support.
  \details   This header file is used for GDT support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __KERNEL_GDT_H
#define __KERNEL_GDT_H

#if defined(__cplusplus)
extern "C" {
#endif

	/** 
	   \brief Sets an GDT gate.
	*/
	void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
	/** 
	   \brief Installs the GDT to the kernel.

	   This function installs the Global Descriptor Table (GDT) into the kernel.
	*/
	void gdt_install();

#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif
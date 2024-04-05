//Modified from GCC runtime
/*
 * Copyright (C) 2007, 2008, 2009 Free Software Foundation, Inc.
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or (at your option) any
 * later version.
 * 
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * Under Section 7 of GPL version 3, you are granted additional
 * permissions described in the GCC Runtime Library Exception, version
 * 3.1, as published by the Free Software Foundation.
 * 
 * You should have received a copy of the GNU General Public License and
 * a copy of the GCC Runtime Library Exception along with this program;
 * see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

enum {
	CPUID_FEAT_ECX_SSE3         = 1 << 0,  // streaming SIMD extensions 3 (SSE3)
	CPUID_FEAT_ECX_MONITOR      = 1 << 3,  // monitor/mwait
	CPUID_FEAT_ECX_DS_CPL       = 1 << 4,  // CPL qualified debug store
	CPUID_FEAT_ECX_VMX          = 1 << 5,  // virtual machine extensions
	CPUID_FEAT_ECX_SMX          = 1 << 6,  // safer mode extensions
	CPUID_FEAT_ECX_EST          = 1 << 7,  // enhanced Intel SpeedStep(R) technology
	CPUID_FEAT_ECX_TM2          = 1 << 8,  // thermal monitor 2
	CPUID_FEAT_ECX_SSSE3        = 1 << 9,  // supplemental streaming SIMD extensions 3 (SSSSE3)
	CPUID_FEAT_ECX_CNXT_ID      = 1 << 10, // L1 context ID
	CPUID_FEAT_ECX_CMPXCHG16B   = 1 << 13, // cmpxchg16b available (obviously)
	CPUID_FEAT_ECX_xTPR_UPDATE  = 1 << 14, // xTPR update control
	CPUID_FEAT_ECX_PDCM         = 1 << 15, // performance and debug capability
	CPUID_FEAT_ECX_DCA          = 1 << 18, // memory-mapped device prefetching
	CPUID_FEAT_ECX_SSE4_1       = 1 << 19, // SSE4.1
	CPUID_FEAT_ECX_SSE4_2       = 1 << 20, // SSE4.2
	CPUID_FEAT_ECX_x2APIC       = 1 << 21, // x2APIC available
	CPUID_FEAT_ECX_MOVBE        = 1 << 22, // movbe available
	CPUID_FEAT_ECX_POPCNT       = 1 << 23, // popcnt available (sounds rude)
	CPUID_FEAT_ECX_XSAVE        = 1 << 26, // xsave/xrstor/xsetbv/xgetbv supported
	CPUID_FEAT_ECX_OSXSAVE      = 1 << 27, // xsetbv/xgetbv has been enabled

	CPUID_FEAT_EDX_x87          = 1 << 0,  // x86 FPU on chip
	CPUID_FEAT_EDX_VME          = 1 << 1,  // virtual-8086 mode enhancement
	CPUID_FEAT_EDX_DE           = 1 << 2,  // debugging extensions
	CPUID_FEAT_EDX_PSE          = 1 << 3,  // page size extensions
	CPUID_FEAT_EDX_TSC          = 1 << 4,  // timestamp counter
	CPUID_FEAT_EDX_MSR          = 1 << 5,  // rdmsr/wrmsr
	CPUID_FEAT_EDX_PAE          = 1 << 6,  // page address extensions
	CPUID_FEAT_EDX_MCE          = 1 << 7,  // machine check exception
	CPUID_FEAT_EDX_CX8          = 1 << 8,  // cmpxchg8b supported
	CPUID_FEAT_EDX_APIC         = 1 << 9,  // APIC on a chip
	CPUID_FEAT_EDX_SEP          = 1 << 11, // sysenter/sysexit
	CPUID_FEAT_EDX_MTRR         = 1 << 12, // memory type range registers
	CPUID_FEAT_EDX_PGE          = 1 << 13, // PTE global bit (PTE_GLOBAL)
	CPUID_FEAT_EDX_MCA          = 1 << 14, // machine check architecture
	CPUID_FEAT_EDX_CMOV         = 1 << 15, // conditional move/compare instructions
	CPUID_FEAT_EDX_PAT          = 1 << 16, // page attribute table
	CPUID_FEAT_EDX_PSE36        = 1 << 17, // page size extension
	CPUID_FEAT_EDX_PSN          = 1 << 18, // processor serial number
	CPUID_FEAT_EDX_CLFSH        = 1 << 19, // cflush instruction
	CPUID_FEAT_EDX_DS           = 1 << 21, // debug store
	CPUID_FEAT_EDX_ACPI         = 1 << 22, // thermal monitor and clock control
	CPUID_FEAT_EDX_MMX          = 1 << 23, // MMX technology
	CPUID_FEAT_EDX_FXSR         = 1 << 24, // fxsave/fxrstor
	CPUID_FEAT_EDX_SSE          = 1 << 25, // SSE extensions
	CPUID_FEAT_EDX_SSE2         = 1 << 26, // SSE2 extensions, obviously
	CPUID_FEAT_EDX_SS           = 1 << 27, // self-snoop
	CPUID_FEAT_EDX_HTT          = 1 << 28, // multi-threading (hyper-threading, I think - the afterburner of Intel CPUs)
	CPUID_FEAT_EDX_TM           = 1 << 29, // thermal monitor
	CPUID_FEAT_EDX_PBE          = 1 << 31, // Pend. Brk. EN. (wtf?)
};

#if defined(__i386__) && defined(__PIC__)
/* %ebx may be the PIC register.  */
#if __GNUC__ >= 3
#define __cpuid(level, a, b, c, d)                        \
  __asm__ ("xchg{l}\t{%%}ebx, %1\n\t"                        \
		   "cpuid\n\t"                                        \
		   "xchg{l}\t{%%}ebx, %1\n\t"                        \
		   : "=a" (a), "=r" (b), "=c" (c), "=d" (d)        \
		   : "0" (level))

#define __cpuid_count(level, count, a, b, c, d)                \
  __asm__ ("xchg{l}\t{%%}ebx, %1\n\t"                        \
		   "cpuid\n\t"                                        \
		   "xchg{l}\t{%%}ebx, %1\n\t"                        \
		   : "=a" (a), "=r" (b), "=c" (c), "=d" (d)        \
		   : "0" (level), "2" (count))
#else
/* Host GCCs older than 3.0 weren't supporting Intel asm syntax
   nor alternatives in i386 code.  */
#define __cpuid(level, a, b, c, d)                        \
  __asm__ ("xchgl\t%%ebx, %1\n\t"                        \
		   "cpuid\n\t"                                        \
		   "xchgl\t%%ebx, %1\n\t"                        \
		   : "=a" (a), "=r" (b), "=c" (c), "=d" (d)        \
		   : "0" (level))

#define __cpuid_count(level, count, a, b, c, d)                \
  __asm__ ("xchgl\t%%ebx, %1\n\t"                        \
		   "cpuid\n\t"                                        \
		   "xchgl\t%%ebx, %1\n\t"                        \
		   : "=a" (a), "=r" (b), "=c" (c), "=d" (d)        \
		   : "0" (level), "2" (count))
#endif
#else
#define __cpuid(level, a, b, c, d)                        \
  __asm__ ("cpuid\n\t"                                        \
		   : "=a" (a), "=b" (b), "=c" (c), "=d" (d)        \
		   : "0" (level))

#define __cpuid_count(level, count, a, b, c, d)                \
  __asm__ ("cpuid\n\t"                                        \
		   : "=a" (a), "=b" (b), "=c" (c), "=d" (d)        \
		   : "0" (level), "2" (count))
#endif

/* Return highest supported input value for cpuid instruction.  ext can
   be either 0x0 or 0x8000000 to return highest supported value for
   basic or extended cpuid information.  Function returns 0 if cpuid
   is not supported or whatever cpuid returns in eax register.  If sig
   pointer is non-null, then first four bytes of the signature
   (as found in ebx register) are returned in location pointed by sig.  */

static __inline unsigned int
__get_cpuid_max (unsigned int __ext, unsigned int *__sig)
{
  unsigned int __eax, __ebx, __ecx, __edx;

#ifndef __x86_64__
#if __GNUC__ >= 3
  /* See if we can use cpuid.  On AMD64 we always can.  */
  __asm__ ("pushf{l|d}\n\t"
		   "pushf{l|d}\n\t"
		   "pop{l}\t%0\n\t"
		   "mov{l}\t{%0, %1|%1, %0}\n\t"
		   "xor{l}\t{%2, %0|%0, %2}\n\t"
		   "push{l}\t%0\n\t"
		   "popf{l|d}\n\t"
		   "pushf{l|d}\n\t"
		   "pop{l}\t%0\n\t"
		   "popf{l|d}\n\t"
		   : "=&r" (__eax), "=&r" (__ebx)
		   : "i" (0x00200000));
#else
/* Host GCCs older than 3.0 weren't supporting Intel asm syntax
   nor alternatives in i386 code.  */
  __asm__ ("pushfl\n\t"
		   "pushfl\n\t"
		   "popl\t%0\n\t"
		   "movl\t%0, %1\n\t"
		   "xorl\t%2, %0\n\t"
		   "pushl\t%0\n\t"
		   "popfl\n\t"
		   "pushfl\n\t"
		   "popl\t%0\n\t"
		   "popfl\n\t"
		   : "=&r" (__eax), "=&r" (__ebx)
		   : "i" (0x00200000));
#endif

  if (!((__eax ^ __ebx) & 0x00200000))
	return 0;
#endif

  /* Host supports cpuid.  Return highest supported cpuid input value.  */
  __cpuid (__ext, __eax, __ebx, __ecx, __edx);

  if (__sig)
	*__sig = __ebx;

  return __eax;
}

/* Return cpuid data for requested cpuid level, as found in returned
   eax, ebx, ecx and edx registers.  The function checks if cpuid is
   supported and returns 1 for valid cpuid information or 0 for
   unsupported cpuid level.  All pointers are required to be non-null.  */

static __inline int
__get_cpuid (unsigned int __level,
			 unsigned int *__eax, unsigned int *__ebx,
			 unsigned int *__ecx, unsigned int *__edx)
{
  unsigned int __ext = __level & 0x80000000;

  if (__get_cpuid_max (__ext, 0) < __level)
	return 0;

  __cpuid (__level, *__eax, *__ebx, *__ecx, *__edx);
  return 1;
}
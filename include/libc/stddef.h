#ifndef __STDDEF_H
#define __STDDEF_H

#if defined(__cplusplus)
extern "C" {
#endif


	#define NULL ((void * ) 0)
	
	typedef signed int ptrdiff_t;
	typedef int wchar_t;
	typedef unsigned int size_t;

#if defined(__cplusplus)
} /* extern "C" */
#endif
#endif
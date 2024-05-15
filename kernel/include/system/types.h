#ifndef __SYSTEM_TYPES_H
#define __SYSTEM_TYPES_H

#define true 1
#define false 0



#if defined(__cplusplus)
extern "C" {
#endif

	/**
		\typedef char int8_t
		\brief 8-bit integer type
	*/
	typedef char int8_t;
	/**
		\typedef unsigned char int8_t
		\brief Unsigned 8-bit integer type
	*/
	typedef unsigned char uint8_t;

	/**
		\typedef short int16_t
		\brief 16-bit integer type
	*/
	typedef short int16_t;
	/**
		\typedef unsigned short uint16_t
		\brief Unsigned 16-bit integer type
	*/
	typedef unsigned short uint16_t;

	/**
		\typedef int int32_t
		\brief 32-bit integer type
	*/
	typedef int int32_t;
	/**
		\typedef unsigned int uint32_t
		\brief Unsigned 32-bit integer type
	*/
	typedef unsigned int uint32_t;

	/**
		\typedef long long int int64_t
		\brief 64-bit integer type
	*/
	typedef long long int int64_t;
	/**
		\typedef unsigned long long int uint64_t
		\brief Unsigned 64-bit integer type
	*/
	typedef unsigned long long int uint64_t;
	
	typedef unsigned int size_t;
	
	typedef size_t ssize_t;
	
	typedef long off_t;
	
	typedef int bool;

	
#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
    
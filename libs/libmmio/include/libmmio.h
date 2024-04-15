#ifndef __LIBMMIO_H
#define __LIBMMIO_H

#include <system/types.h>

#if defined(__cplusplus)
extern "C" {
#endif
	uint8_t mmioRead8 (uint64_t p_address);
	uint16_t mmioRead16 (uint64_t p_address);
	uint32_t mmioRead32 (uint64_t p_address);
	uint64_t mmioRead64 (uint64_t p_address);

	void mmioWrite8 (uint64_t p_address,uint8_t p_value);
	void mmioWrite16 (uint64_t p_address,uint16_t p_value);
	void mmioWrite32 (uint64_t p_address,uint32_t p_value);
	void mmioWrite64 (uint64_t p_address,uint64_t p_value);
#if defined(__cplusplus)
} /* extern "C" */
#endif



#endif
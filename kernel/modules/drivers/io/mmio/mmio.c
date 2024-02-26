#include <drivers/io/mmio.h>
#include <system/types.h>

uint8_t mmioRead8 (uint64_t p_address) {
	return *((volatile uint8_t*)(p_address));
}

uint16_t mmioRead16 (uint64_t p_address) {
	return *((volatile uint16_t*)(p_address));
}

uint32_t mmioRead32 (uint64_t p_address) {
	return *((volatile uint32_t*)(p_address));
}

uint64_t mmioRead64 (uint64_t p_address) {
	return *((volatile uint64_t*)(p_address));    
}

void mmioWrite8 (uint64_t p_address,uint8_t p_value) {
	(*((volatile uint8_t*)(p_address)))=(p_value);
}

void mmioWrite16 (uint64_t p_address,uint16_t p_value) {
	(*((volatile uint16_t*)(p_address)))=(p_value);    
}

void mmioWrite32 (uint64_t p_address,uint32_t p_value) {
	(*((volatile uint32_t*)(p_address)))=(p_value);
}

void mmioWrite64 (uint64_t p_address,uint64_t p_value) {
	(*((volatile uint64_t*)(p_address)))=(p_value);    
}

#ifndef _STDINT_H_
#include <stdint.h>
#endif

#define MEMORY_SIZE 0x10000

void mem_init();

uint8_t fetch(uint16_t address);

uint16_t store(uint16_t address, uint8_t value);
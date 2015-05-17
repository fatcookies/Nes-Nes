#ifndef _STDINT_H_
#include <stdint.h>
#endif

#define MEMORY_SIZE 8192

uint8_t fetch(uint16_t address);

uint16_t store(uint16_t address, uint8_t value);
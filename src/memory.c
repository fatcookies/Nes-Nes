#include "memory.h"

uint8_t mem[MEMORY_SIZE];

uint8_t fetch(uint16_t address) {
	if(address <= MEMORY_SIZE) {
		return mem[address];
	} else {
		// error;
		return 0;
	}
}

uint16_t store(uint16_t address, uint8_t value) {
	if(address <= MEMORY_SIZE) {
		mem[address] = value;
		return 1;
	} else {
		// error;
		return 0;
	}	
}
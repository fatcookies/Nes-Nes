#include "memory.h"

static inline uint16_t handle_mirrors(uint16_t address);
uint8_t mem[MEMORY_SIZE];

uint8_t fetch(uint16_t address) {
	if(address <= MEMORY_SIZE) {
		return mem[handle_mirrors(address)];
	} else {
		// error;
		return 0;
	}
}

static inline uint16_t handle_mirrors(uint16_t address) {
	if(address >= 0x800 && address < 0x1000) {
		address -= 0x800;
	} else if (address >= 0x1000 && address < 0x1800) {
		address -= 0x1000;
	} else if (address >= 0x1800 && address < 0x2000) {
		address -= 0x1800;
	} else if (address >= 0x2008 && address < 0x4000) {
		address -= 0x2000;

	}
	return address;
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
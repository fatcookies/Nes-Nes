#include <stdlib.h>

#include "ppu_memory.h"


void ppumem_init() {
	ppu_mem = malloc(sizeof(uint8_t) * PPU_MEMORY_SIZE);
}

uint8_t ppu_fetch(uint16_t address) {
	return ppu_mem[address];
}

uint16_t ppu_store(uint16_t address, uint8_t value) {
	return ppu_mem[address] = value;
	return 0;
}
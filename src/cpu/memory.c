#include <stdlib.h>

#include "memory.h"
#include "io.h"

uint8_t* handle_input(uint16_t address);
uint8_t* handle_output(uint16_t address);

uint8_t *mem;

void mem_init() {
	mem = malloc((sizeof mem) * MEMORY_SIZE);
}

uint8_t fetch(uint16_t address) {
	if(address <= MEMORY_SIZE) {
		return *(handle_input(address));
		//return mem[address];
	} else {
		// error;
		return 0;
	}
}

uint16_t store(uint16_t address, uint8_t value) {
	if(address <= MEMORY_SIZE) {
		*handle_output(address) = value;
		return 1;
	} else {
		// error;
		return 0;
	}	
}

uint8_t* handle_input(uint16_t address) {

	if((address >= 0x800) && (address < 0x1000)) {
		return &(mem[address - 0x800]);

	} else if ((address >= 0x1000) && (address < 0x1800)) {
		return &(mem[address - 0x1000]);

	} else if ((address >= 0x1800) && (address < 0x2000)) {
		return &(mem[address - 0x1800]);

	} else if ((address >= 0x2000) && (address < 0x2008)) {
		return handle_ppu_input(address);;
		
	} else if ((address >= 0x2008) && (address < 0x4000)) {
		return handle_ppu_input(0x2000 + (address % 8)); 
		
	} 
	return &(mem[address]);
}

uint8_t* handle_output(uint16_t address) {

	if((address >= 0x800) && (address < 0x1000)) {
		return &(mem[address - 0x800]);

	} else if ((address >= 0x1000) && (address < 0x1800)) {
		return &(mem[address - 0x1000]);

	} else if ((address >= 0x1800) && (address < 0x2000)) {
		return &(mem[address - 0x1800]);

	} else if ((address >= 0x2000) && (address < 0x2008)) {
		return handle_ppu_output(address);;
		
	} else if ((address >= 0x2008) && (address < 0x4000)) {
		return handle_ppu_output(0x2000 + (address % 8)); 
		
	} 
	return &(mem[address]);
}




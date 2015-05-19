#include <stdlib.h>

#include "ppu.h"

void ppu_init() {
	ppu_registers = (ppu_register*) malloc(sizeof (ppu_register));

	ppu_registers->control1       = 0;
	ppu_registers->control2       = 0;
	ppu_registers->status         = 0xA0;
	ppu_registers->sprite_address = 0;
	ppu_registers->sprite_data    = 0;
	ppu_registers->scroll         = 0;
	ppu_registers->address        = 0;
	ppu_registers->data           = 0;
}

uint8_t* handle_ppu_io(uint16_t address) {
	switch(address) {
		case 0x2000: return &(ppu_registers->control1); break;
		case 0x2001: return &(ppu_registers->control2); break;
		case 0x2002: return &(ppu_registers->status); break;
		case 0x2003: return &(ppu_registers->sprite_address); break;
		case 0x2004: return &(ppu_registers->sprite_data); break;
		case 0x2005: return &(ppu_registers->scroll); break;
		case 0x2006: return &(ppu_registers->address); break;
		case 0x2007: return &(ppu_registers->data); break;
	}
	
	return 0;
}
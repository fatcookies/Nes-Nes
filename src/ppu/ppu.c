#include <stdlib.h>

#include "ppu.h"
#include "ppu_memory.h"

uint8_t temp;

void ppu_init() {
	ppu_registers = (ppu_register*) malloc(sizeof (ppu_register));

	ppu_registers->control1       = 0;
	ppu_registers->control2       = 0;
	ppu_registers->status         = 0xA0;
	ppu_registers->sprite_address = 0;
	ppu_registers->sprite_data    = 0;
	ppu_registers->cam_position_x = 0;
	ppu_registers->cam_position_y = 0;
	ppu_registers->fulladdress    = 0;
	ppu_registers->data           = 0;
}

void ppu_exec() {

}

uint8_t* handle_ppu_output(uint16_t address) {
	switch(address) {
		case 0x2000: return &(ppu_registers->control1); break;
		case 0x2001: return &(ppu_registers->control2); break;
		case 0x2003: return &(ppu_registers->sprite_address); break;
		case 0x2004:
			ppu_registers->sprite_address++;
			return ppu_oam + ppu_registers->sprite_address - 1;
			break;
		case 0x2005: 
			TOGGLE_LSB_WRITTEN();
			return IF_LSB_WRITTEN() ? &(ppu_registers->cam_position_x) : &(ppu_registers->cam_position_y); 
			break;
		case 0x2006: 
			TOGGLE_LSB_WRITTEN();
			uint8_t* ad = (uint8_t*) &(ppu_registers->fulladdress);
			return IF_LSB_WRITTEN() ? ad+1 : ad; 
			break;
		case 0x2007: return ppu_mem + ppu_registers->fulladdress; break;
	}
	
	return 0;
}

uint8_t* handle_ppu_input(uint16_t address) {
	switch(address) {
		case 0x2002: 
			temp = ppu_registers->status;
			// clear after reading $2002 and at dot 1 of the pre-render line.
			return &temp;
			break;
		case 0x2004: return ppu_oam + ppu_registers->sprite_address; break;
		case 0x2007: return ppu_mem + ppu_registers->fulladdress; break;
	}
	
	return 0;
}
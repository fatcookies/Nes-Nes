#ifndef _STDINT_H_
#include <stdint.h>
#endif

typedef struct {
	uint8_t control1;
	uint8_t control2;
	uint8_t status;
	uint8_t sprite_address;
	uint8_t sprite_data;
	uint8_t scroll;
	uint8_t address;
	uint8_t data;
} ppu_register;

ppu_register * ppu_registers;

uint8_t* handle_ppu_io(uint16_t address);

void ppu_init();
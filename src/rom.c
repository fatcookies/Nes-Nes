#include <stdlib.h>
#include <stdio.h>

#include "rom.h"

void romtest();


void rom_init() {
	if(prg_rom && chr_rom) {
		free(prg_rom);
		free(chr_rom);
	}

	romtest();
}

void romtest() {
	FILE *f;
	prg_rom = malloc((sizeof(uint8_t) * 0x8000));
	chr_rom = malloc((sizeof(uint8_t) * 0x2000));

	f = fopen("smb.nes", "rb");
	fseek(f,16,0);
	if (f) {
    	fread(prg_rom, 1, 0x8000, f);
    	fread(chr_rom, 1, 0x2000, f);
	}
}


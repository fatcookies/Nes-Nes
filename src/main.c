#include "rom.h"
#include "cpu/cpu.h"
#include "cpu/memory.h"
#include "ppu/ppu.h"
#include "ppu/ppu_memory.h"
#include <stdio.h>

void test();


int main() {
	test();
	return 0;
}


void test() {
	rom_init();
	mem_init();
	cpu_init();
	ppumem_init();
	ppu_init();


	uint32_t i;
	
	for(i = 0; i < 0x8000; i++) {
		store((i+0x8000),prg_rom[i]);
	}
	for(i = 0; i < 0x2000; i++) {
		ppu_store((i+PATTERN_TABLE_0),chr_rom[i]);
	}

	
	for(i=0; i < 500;i++) {
		ppu_exec();
		exec();
	}
	
	/*
	store(0x2006,0x10);
	store(0x2006,0x12);
	ppu_mem[0x1012] = 0x69;

	printf("ppuaddr=0x%x\n",ppu_registers->fulladdress);
	printf("0x1012 ppu = 0x%x\n",fetch(0x2007));
	*/
	
	printf("\n\npc= 0x%x\n",registers->pc);
	printf("sp= 0x%x\n",registers->sp);
	printf("acc=0x%x\n",registers->acc);
	printf("x=  0x%x\n",registers->x);
	printf("y=  0x%x\n",registers->y);

}

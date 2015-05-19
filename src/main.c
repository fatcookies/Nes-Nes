#include "cpu/cpu.h"
#include "cpu/memory.h"
#include "ppu/ppu.h"
#include <stdio.h>

void test();


int main() {
	test();
	return 0;
}


void test() {
	FILE *f;
	unsigned char buffer[0x10000];
	f = fopen("smb.nes", "rb");
	fseek(f,16,0);
	if (f) {
    	fread(buffer, 1, sizeof buffer, f);
	}


	mem_init();
	cpu_init();
	ppu_init();


	uint32_t i;
	
	for(i = 0; i < 0x8000; i++) {
		store((i+0x8000),buffer[i]);
	}


	for(i=0; i < 500;i++) {
		exec();
	}
	

	printf("\n\npc= 0x%x\n",registers->pc);
	printf("sp= 0x%x\n",registers->sp);
	printf("acc=0x%x\n",registers->acc);
	printf("x=  0x%x\n",registers->x);
	printf("y=  0x%x\n",registers->y);

}

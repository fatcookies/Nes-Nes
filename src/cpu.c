#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "memory.h"
#include "stack.h"
#include "addressing.h"

#include "instructions/arithmetic.h"
#include "instructions/loadstore.h"
#include "instructions/registertransfer.h"

void cpu_init() {
	if(registers && flags) {
		free(registers);
		free(flags);
	}

	registers = malloc(sizeof (reg));
	flags = malloc(sizeof (flags));

	registers->pc = 512;
	registers->sp = 0x1FF;
	registers->acc = 0;
	registers->x = 0;
	registers->y = 0;

	flags->carry = 0;
	flags->zero = 0;
	flags->interrupt = 0;
	flags->dec = 0;
	flags->break_cmd = 0;
	flags->overflow = 0;
	flags->sign = 0;
}

inline uint8_t cpu_status() {
	return (flags->carry & 1) | ((flags->zero & 1) << 1) 
		| ((flags->interrupt & 1) << 2) | ((flags->dec& 1) << 3)
		| ((flags->break_cmd & 1) << 4) | ((flags->overflow & 1) <<6) 
		| ((flags->sign & 1) << 7);
}

void reset() {
	cpu_init();
}

inline uint8_t next() {
	uint8_t res = fetch(registers->pc);
	registers->pc = registers->pc + 1;
	return res;
}

inline uint16_t next16() {
	uint8_t a = next();
	uint8_t b = next();
	return combine(b,a);
}

inline uint16_t fetch16(uint16_t address) {
	uint8_t a = fetch(address);
	uint8_t b = fetch(address + 1);
	return combine(b,a);
}

void exec() {

	uint8_t ins = next();
	

	switch(ins) {
		// ADC 
		case 0x69: ins_adc(next());              break;
		case 0x65: ins_adc(fetch(zeropage()));   break;
		case 0x75: ins_adc(fetch(zeropage_x())); break;
		case 0x6D: ins_adc(fetch(absolute()));   break;
		case 0x7D: ins_adc(fetch(absolute_x())); break;
		case 0x79: ins_adc(fetch(absolute_y())); break;
		case 0x61: ins_adc(fetch(indirect_x())); break;
		case 0x71: ins_adc(fetch(indirect_y())); break;

		// LDA
		case 0xA9: ins_lda(next());              break;
		case 0xA5: ins_lda(fetch(zeropage()));   break;
		case 0xB5: ins_lda(fetch(zeropage_x())); break;
		case 0xAD: ins_lda(fetch(absolute()));   break;
		case 0xBD: ins_lda(fetch(absolute_x())); break;
		case 0xB9: ins_lda(fetch(absolute_y())); break;
		case 0xA1: ins_lda(fetch(indirect_x())); break;
		case 0xB1: ins_lda(fetch(indirect_y())); break;

		// LDX
		case 0xA2: ins_ldx(next());              break;
		case 0xA6: ins_ldx(fetch(zeropage()));   break;
		case 0xB6: ins_ldx(fetch(zeropage_y())); break;
		case 0xAE: ins_ldx(fetch(absolute()));   break;
		case 0xBE: ins_ldx(fetch(absolute_y())); break;

		// LDY
		case 0xA0: ins_ldy(next());              break;
		case 0xA4: ins_ldy(fetch(zeropage()));   break;
		case 0xB4: ins_ldy(fetch(zeropage_x())); break;
		case 0xAC: ins_ldy(fetch(absolute()));   break;
		case 0xBC: ins_ldy(fetch(absolute_x())); break;

		//STA
		case 0x85: ins_sta(fetch(zeropage()));   break;
		case 0x95: ins_sta(fetch(zeropage_x())); break;
		case 0x8D: ins_sta(fetch(absolute()));   break;
		case 0x9D: ins_sta(fetch(absolute_x())); break;
		case 0x99: ins_sta(fetch(absolute_y())); break;
		case 0x81: ins_sta(fetch(indirect_x())); break;
		case 0x91: ins_sta(fetch(indirect_y())); break;

		//STX
		case 0x86: ins_stx(fetch(zeropage())); break;
		case 0x96: ins_stx(fetch(zeropage_y())); break;
		case 0x8E: ins_stx(fetch(absolute())); break;

		//STY
		case 0x84: ins_stx(fetch(zeropage())); break;
		case 0x94: ins_stx(fetch(zeropage_x())); break;
		case 0x8C: ins_stx(fetch(absolute())); break;
	}

}

int main() {
	cpu_init();
	ins_lda(69);
	printf("acc = %u\n",registers->acc);
	printf("v = %u, c = %u\n", flags->overflow, flags->carry);
	ins_sbc(60);
	printf("acc = %u\n",registers->acc);
	printf("v = %u, c = %u\n", flags->overflow, flags->carry);
	
	return 0;
}

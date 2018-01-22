#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
#include "memory.h"
#include "stack.h"
#include "addressing.h"

#include "instructions/loadstore.h"
#include "instructions/registertransfer.h"
#include "instructions/stackops.h"
#include "instructions/logic.h"
#include "instructions/arithmetic.h"
#include "instructions/incdec.h"
#include "instructions/shifts.h"
#include "instructions/jumps.h"
#include "instructions/branches.h"
#include "instructions/statusflags.h"
#include "instructions/misc.h"


void cpu_init() {
	if(registers && flags) {
		free(registers);
		free(flags);
	}

	cycles = 0;
	registers = malloc(sizeof (reg));
	flags = malloc(sizeof (flags));

	registers->pc = 0x8000;
	registers->sp = 0x1FF;
	registers->acc = 0;
	registers->x = 0;
	registers->y = 0;

	*flags = 0;
}

uint8_t cpu_status() {
	return *flags;
}

void reset() {
	cpu_init();
}

uint8_t next() {
	registers->pc = registers->pc + 1;
	uint8_t res = fetch(registers->pc);
	return res;
}

uint16_t next16() {
	uint8_t a = next();
	uint8_t b = next();
	return combine(b,a);
}

uint16_t fetch16(uint16_t address) {
	uint8_t a = fetch(address);
	uint8_t b = fetch(address + 1);
	return combine(b,a);
}

void tick() {
	if(cycles) {
		cycles--;
	} else {
		exec();
	}
}

void exec() {

	uint8_t ins = fetch(registers->pc);
	printf("%x -----ins %x\n",registers->pc,ins);
	
	uint8_t inc = 0;
	switch(ins) {

		// Load/Store Instructions
		// LDA
		case 0xA9: ins_lda(next());              cycles+=2; break;
		case 0xA5: ins_lda(fetch(zeropage()));   cycles+=3; break;
		case 0xB5: ins_lda(fetch(zeropage_x())); cycles+=4; break;
		case 0xAD: ins_lda(fetch(absolute()));   cycles+=4; break;
		case 0xBD: ins_lda(fetch(absolute_x_pages())); cycles+=4; break;
		case 0xB9: ins_lda(fetch(absolute_y_pages())); cycles+=4; break;
		case 0xA1: ins_lda(fetch(indirect_x())); cycles+=6; break;
		case 0xB1: ins_lda(fetch(indirect_y_pages())); cycles+=5; break;

		// LDX
		case 0xA2: ins_ldx(next());              cycles+=2; break;
		case 0xA6: ins_ldx(fetch(zeropage()));   cycles+=3; break;
		case 0xB6: ins_ldx(fetch(zeropage_y())); cycles+=4; break;
		case 0xAE: ins_ldx(fetch(absolute()));   cycles+=4; break;
		case 0xBE: ins_ldx(fetch(absolute_y_pages())); cycles+=4; break;

		// LDY
		case 0xA0: ins_ldy(next());              cycles+=2; break;
		case 0xA4: ins_ldy(fetch(zeropage()));   cycles+=3; break;
		case 0xB4: ins_ldy(fetch(zeropage_x())); cycles+=4; break;
		case 0xAC: ins_ldy(fetch(absolute()));   cycles+=4; break;
		case 0xBC: ins_ldy(fetch(absolute_x_pages())); cycles+=4; break;

		//STA
		case 0x85: ins_sta(zeropage());   cycles+=3; break;
		case 0x95: ins_sta(zeropage_x()); cycles+=4; break;
		case 0x8D: ins_sta(absolute());   cycles+=4; break;
		case 0x9D: ins_sta(absolute_x()); cycles+=5; break;
		case 0x99: ins_sta(absolute_y()); cycles+=5; break;
		case 0x81: ins_sta(indirect_x()); cycles+=6; break;
		case 0x91: ins_sta(indirect_y()); cycles+=6; break;

		//STX
		case 0x86: ins_stx(zeropage());   cycles+=3; break;
		case 0x96: ins_stx(zeropage_y()); cycles+=4; break;
		case 0x8E: ins_stx(absolute());   cycles+=4; break;

		//STY
		case 0x84: ins_stx(zeropage());   cycles+=3; break;
		case 0x94: ins_stx(zeropage_x()); cycles+=4; break;
		case 0x8C: ins_stx(absolute());   cycles+=4; break;

		// Register Transfers
		case 0xAA: ins_tax(); cycles+=2; break;
		case 0xA8: ins_tay(); cycles+=2; break;
		case 0x8A: ins_txa(); cycles+=2; break;
		case 0x98: ins_tya(); cycles+=2; break;

		// Stack Operations
		case 0xBA: ins_tsx(); cycles+=2; break;
		case 0x9A: ins_txs(); cycles+=2; break;
		case 0x48: ins_pha(); cycles+=3; break;
		case 0x08: ins_php(); cycles+=3; break;
		case 0x68: ins_pla(); cycles+=4; break;
		case 0x28: ins_plp(); cycles+=4; break;

		// Logical Operations
		// AND
		case 0x29: ins_and(next());               cycles+=2; break;
		case 0x25: ins_and(fetch(zeropage()));    cycles+=3; break;
		case 0x35: ins_and(fetch(zeropage_x()));  cycles+=4; break;
		case 0x2D: ins_and(fetch(absolute()));    cycles+=4; break;
		case 0x3D: ins_and(fetch(absolute_x_pages()));  cycles+=4; break;
		case 0x39: ins_and(fetch(absolute_y_pages()));  cycles+=4; break;
		case 0x21: ins_and(fetch(indirect_x()));  cycles+=6; break;
		case 0x31: ins_and(fetch(indirect_y_pages()));  cycles+=5; break;

		// EOR
		case 0x49: ins_eor(next());               cycles+=2; break;
		case 0x45: ins_eor(fetch(zeropage()));    cycles+=3; break;
		case 0x55: ins_eor(fetch(zeropage_x()));  cycles+=4; break;
		case 0x4D: ins_eor(fetch(absolute()));    cycles+=4; break;
		case 0x5D: ins_eor(fetch(absolute_x_pages()));  cycles+=4; break;
		case 0x59: ins_eor(fetch(absolute_y_pages()));  cycles+=4; break;
		case 0x41: ins_eor(fetch(indirect_x()));  cycles+=6; break;
		case 0x51: ins_eor(fetch(indirect_y_pages()));  cycles+=5; break;


		// ORA
		case 0x09: ins_ora(next());               cycles+=2; break;
		case 0x05: ins_ora(fetch(zeropage()));    cycles+=3; break;
		case 0x15: ins_ora(fetch(zeropage_x()));  cycles+=4; break;
		case 0x0D: ins_ora(fetch(absolute()));    cycles+=4; break;
		case 0x1D: ins_ora(fetch(absolute_x_pages()));  cycles+=4; break;
		case 0x19: ins_ora(fetch(absolute_y_pages()));  cycles+=4; break;
		case 0x01: ins_ora(fetch(indirect_x()));  cycles+=6; break;
		case 0x11: ins_ora(fetch(indirect_y_pages()));  cycles+=5; break;

		// BIT
		case 0x24: ins_bit(fetch(zeropage())); cycles+=3; break;
		case 0x2C: ins_bit(fetch(absolute())); cycles+=4; break;


		// Arithmetic Operations
		// ADC 
		case 0x69: ins_adc(next());              cycles+=2; break;
		case 0x65: ins_adc(fetch(zeropage()));   cycles+=3; break;
		case 0x75: ins_adc(fetch(zeropage_x())); cycles+=4; break;
		case 0x6D: ins_adc(fetch(absolute()));   cycles+=4; break;
		case 0x7D: ins_adc(fetch(absolute_x_pages())); cycles+=4; break;
		case 0x79: ins_adc(fetch(absolute_y_pages())); cycles+=4; break;
		case 0x61: ins_adc(fetch(indirect_x())); cycles+=6; break;
		case 0x71: ins_adc(fetch(indirect_y_pages())); cycles+=5; break;

		// SBC
		case 0xE9: ins_sbc(next());              cycles+=2; break;
		case 0xE5: ins_sbc(fetch(zeropage()));   cycles+=3; break;
		case 0xF5: ins_sbc(fetch(zeropage_x())); cycles+=4; break;
		case 0xED: ins_sbc(fetch(absolute()));   cycles+=4; break;
		case 0xFD: ins_sbc(fetch(absolute_x_pages())); cycles+=4; break;
		case 0xF9: ins_sbc(fetch(absolute_y_pages())); cycles+=4; break;
		case 0xE1: ins_sbc(fetch(indirect_x())); cycles+=6; break;
		case 0xF1: ins_sbc(fetch(indirect_y_pages())); cycles+=5; break;

		// CMP
		case 0xC9: ins_cmp(next());              cycles+=2; break;
		case 0xC5: ins_cmp(fetch(zeropage()));   cycles+=3; break;
		case 0xD5: ins_cmp(fetch(zeropage_x())); cycles+=4; break;
		case 0xCD: ins_cmp(fetch(absolute()));   cycles+=4; break;
		case 0xDD: ins_cmp(fetch(absolute_x_pages())); cycles+=4; break;
		case 0xD9: ins_cmp(fetch(absolute_y_pages())); cycles+=4; break;
		case 0xC1: ins_cmp(fetch(indirect_x())); cycles+=6; break;
		case 0xD1: ins_cmp(fetch(indirect_y_pages())); cycles+=5; break;

		//CPX
		case 0xE0: ins_cpx(next());            cycles+=2; break;
		case 0xE4: ins_cpx(fetch(zeropage())); cycles+=3; break;
		case 0xEC: ins_cpx(fetch(absolute())); cycles+=4; break;

		//CPY
		case 0xC0: ins_cpy(next());            cycles+=2; break;
		case 0xC4: ins_cpy(fetch(zeropage())); cycles+=3; break;
		case 0xCC: ins_cpy(fetch(absolute())); cycles+=4; break;

		// Increment and Decrement Operations
		// INC
		case 0xE6: ins_inc(zeropage());   cycles+=5; break;
		case 0xF6: ins_inc(zeropage_x()); cycles+=6; break;
		case 0xEE: ins_inc(absolute());   cycles+=6; break;
		case 0xFE: ins_inc(absolute_x()); cycles+=7; break;

		case 0xE8: ins_inx(); cycles+=2; break;
		case 0xC8: ins_iny(); cycles+=2; break;
		
		// DEC
		case 0xC6: ins_dec(zeropage());   cycles+=5; break;
		case 0xD6: ins_dec(zeropage_x()); cycles+=6; break;
		case 0xCE: ins_dec(absolute());   cycles+=6; break;
		case 0xDE: ins_dec(absolute_x()); cycles+=7; break;

		case 0x88: ins_dey(); cycles+=2; break;
		case 0xCA: ins_dex(); cycles+=2; break;

		// Shift Operations
		// ASL
		case 0x0A: ins_asl(0,0);            cycles+=2; break;
		case 0x06: ins_asl(1,zeropage());   cycles+=5; break;
		case 0x16: ins_asl(1,zeropage_x()); cycles+=6; break;
		case 0x0E: ins_asl(1,absolute());   cycles+=6; break;
		case 0x1E: ins_asl(1,absolute_x()); cycles+=7; break;

		// LSR
		case 0x4A: ins_lsr(0,0);            cycles+=2; break;
		case 0x46: ins_lsr(1,zeropage());   cycles+=5; break;
		case 0x56: ins_lsr(1,zeropage_x()); cycles+=6; break;
		case 0x4E: ins_lsr(1,absolute());   cycles+=6; break;
		case 0x5E: ins_lsr(1,absolute_x()); cycles+=7; break;

		// ROL
		case 0x2A: ins_rol(0,0);            cycles+=2; break;
		case 0x26: ins_rol(1,zeropage());   cycles+=5; break;
		case 0x36: ins_rol(1,zeropage_x()); cycles+=6; break;
		case 0x2E: ins_rol(1,absolute());   cycles+=6; break;
		case 0x3E: ins_rol(1,absolute_x()); cycles+=7; break;

		// ROR
		case 0x6A: ins_rol(0,0);            cycles+=2; break;
		case 0x66: ins_rol(1,zeropage());   cycles+=5; break;
		case 0x76: ins_rol(1,zeropage_x()); cycles+=6; break;
		case 0x6E: ins_rol(1,absolute());   cycles+=6; break;
		case 0x7E: ins_rol(1,absolute_x()); cycles+=7; break;

		// Jumps and Call Operations
		//JMP
		case 0x4C: ins_jmp(absolute()); inc = 1; cycles+=3; break;
		case 0x6C: ins_jmp(indirect()); inc = 1; cycles+=5; break;

		case 0x20: ins_jsr(absolute()); inc = 1; cycles+=3; break;
		case 0x60: ins_rts();           inc = 1; cycles+=6; break;

		// Branch Operations
		case 0x90: ins_bcc(next()); inc = 1; cycles+=2; break;
		case 0xB0: ins_bcs(next()); inc = 1; cycles+=2; break;
		case 0xF0: ins_beq(next()); inc = 1; cycles+=2; break;
		case 0x30: ins_bmi(next()); inc = 1; cycles+=2; break;
		case 0xD0: ins_bne(next()); inc = 1; cycles+=2; break;
		case 0x10: ins_bpl(next()); inc = 1; cycles+=2; break;
		case 0x50: ins_bvc(next()); inc = 1; cycles+=2; break;
		case 0x70: ins_bvs(next()); inc = 1; cycles+=2; break;

		// Process Status Flag Operations
		case 0x18: ins_clc(); cycles+=2; break;
		case 0xD8: ins_cld(); cycles+=2; break;
		case 0x58: ins_cli(); cycles+=2; break;
		case 0xB8: ins_clv(); cycles+=2; break;
		case 0x38: ins_sec(); cycles+=2; break;
		case 0xF8: ins_sed(); cycles+=2; break;
		case 0x78: ins_sei(); cycles+=2; break;

		// Misc/System Function Operations
		case 0x00: ins_brk(); inc = 1; cycles+=7; break;
		case 0xEA: ins_nop();          cycles+=2; break;
		case 0x40: ins_rti(); inc = 1; cycles+=6; break;

		default:
			// do something error
		break;
	}
	if(!inc) {
		registers->pc = registers->pc + 1;
	}

}

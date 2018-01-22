#include "loadstore.h"
#include "../cpu.h"
#include "../memory.h"

void ins_lda(uint8_t value) {
	SET_SIGN(value);
	SET_ZERO(value);
	registers->acc = value;
}

void ins_ldx(uint8_t value) {
	SET_SIGN(value);
	SET_ZERO(value);
	registers->x = value;
}

void ins_ldy(uint8_t value) {
	SET_SIGN(value);
	SET_ZERO(value);
	registers->y = value;
}

void ins_sta(uint16_t address) {
	store(address,registers->acc);
}

void ins_stx(uint16_t address) {
	store(address, registers->x);
}

void ins_sty(uint16_t address) {
	store(address, registers->y);
}


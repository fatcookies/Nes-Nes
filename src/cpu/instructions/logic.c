#include "../cpu.h"

void ins_and(uint8_t value) {
	value &= registers->acc;
	SET_SIGN(value);
	SET_ZERO(value);

	registers->acc = value;
}

void ins_eor(uint8_t value) {
	value ^= registers->acc;
	SET_SIGN(value);
	SET_ZERO(value);

	registers->acc = value;
}

void ins_ora(uint8_t value) {
	value |= registers->acc;
	SET_SIGN(value);
	SET_ZERO(value);

	registers->acc = value;
}


void ins_bit(uint8_t value) {
	uint8_t test = registers->acc & value;
	SET_SIGN(test);
	SET_OVERFLOW(((test >> 6) & 1));
	SET_ZERO(test);
}
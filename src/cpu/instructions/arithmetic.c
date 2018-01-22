#include "arithmetic.h"
#include "../cpu.h"

void ins_adc(uint8_t value) {

	uint16_t temp = value + registers->acc + (IF_CARRY() ? 1 : 0);

	SET_ZERO(temp);
	SET_SIGN(temp);
	SET_OVERFLOW(!((registers->acc ^ value) & 0x80) && ((registers->acc ^ temp) & 0x80));
	SET_CARRY(temp > 0xff);

	registers->acc = (uint8_t) temp;
}

void ins_sbc(uint8_t value) {
	int16_t temp = registers->acc - value - (1 - (IF_CARRY() ? 1 : 0));

    SET_SIGN(temp);
    SET_ZERO(temp & 0xff);	
    SET_OVERFLOW(((registers->acc ^ temp) & 0x80) && ((registers->acc ^ value) & 0x80));

    SET_CARRY(temp >= 0);
    registers->acc = (temp & 0xff);
}

void ins_cmp(uint8_t value) {
	value = registers->acc - value;
    SET_CARRY(value < 0x100);
    SET_SIGN(value);
    SET_ZERO(value &= 0xff);
}

void ins_cpx(uint8_t value) {
	value = registers->x - value;
    SET_CARRY(value < 0x100);
    SET_SIGN(value);
    SET_ZERO(value &= 0xff);
}

void ins_cpy(uint8_t value) {
	value = registers->y - value;
    SET_CARRY(value < 0x100);
    SET_SIGN(value);
    SET_ZERO(value &= 0xff);
}
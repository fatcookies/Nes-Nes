#include "../cpu.h"
#include "../stack.h"
#include "stackops.h"

void ins_tsx() {
    SET_SIGN(registers->sp & 0xFF);
    SET_ZERO(registers->sp & 0xFF);
    registers->x = registers->sp & 0xFF;
}

void ins_txs() {
	registers->sp = 0x100 + registers->x;
}

void ins_pha() {
	push(registers->acc);
}

void ins_php() {
	uint8_t status = cpu_status();
    push(status);
}

void ins_pla() {
	uint8_t val = pop();
	SET_SIGN(val);
	SET_ZERO(val);
	registers->acc = val;
}

void ins_plp() {
    *flags = pop();
}
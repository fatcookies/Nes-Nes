#include "../cpu.h"
#include "../stack.h"
#include "stackops.h"

inline void ins_tsx() {
    SET_SIGN(registers->sp);
    SET_ZERO(registers->sp);
    registers->x = registers->sp;
}

inline void ins_txs() {
	registers->sp = registers->x;
}

inline void ins_pha() {
	push(registers->acc);
}

inline void ins_php() {
	uint8_t status = cpu_status();
    push(status);
}

inline void ins_pla() {
	uint8_t val = pop();
	SET_SIGN(val);
	SET_ZERO(val);
	registers->acc = val;
}

inline void ins_plp() {
    *flags = pop();
}
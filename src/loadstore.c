#include "loadstore.h"
#include "cpu.h"
#include "memory.h"

inline void ins_lda(uint8_t value) {
	SET_SIGN(value);
	SET_ZERO(value);
	registers->acc = value;
}

inline void ins_ldx(uint8_t value) {
	SET_SIGN(value);
	SET_ZERO(value);
	registers->x = value;
}

inline void ins_ldy(uint8_t value) {
	SET_SIGN(value);
	SET_ZERO(value);
	registers->y = value;
}

inline void ins_sta(uint16_t address) {
	store(address,registers->acc);
}

inline void ins_stx(uint16_t address) {
	store(address, registers->x);
}

inline void ins_sty(uint16_t address) {
	store(address, registers->y);
}


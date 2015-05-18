#include "registertransfer.h"
#include "../cpu.h"


inline void ins_tax() {
	SET_SIGN(registers->acc);
	SET_ZERO(registers->acc);
	registers->x = registers->acc;
}

inline void ins_tay() {
	SET_SIGN(registers->acc);
	SET_ZERO(registers->acc);
	registers->y = registers->acc;
}

inline void ins_txa() {
	SET_SIGN(registers->x);
	SET_ZERO(registers->x);
	registers->acc = registers->x;
}

inline void ins_tya() {
	SET_SIGN(registers->y);
	SET_ZERO(registers->y);
	registers->acc = registers->y;
}
#include "loadstore.h"
#include "cpu.h"

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

inline void ins_sta(uint8_t value) {
	registers->acc = value;
}

inline void ins_stx(uint8_t value) {
	registers->x = value;
}

inline void ins_sty(uint8_t value) {
	registers->y = value;
}


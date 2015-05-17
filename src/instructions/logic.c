#include "../cpu.h"

inline void ins_and(uint8_t value) {
	value &= registers->acc;
	SET_SIGN(value);
	SET_ZERO(value);

	registers->acc = value;
}

inline void ins_eor(uint8_t value) {
	
}

inline void ins_ora(uint8_t value) {
	
}


inline void ins_bit(uint8_t value) {

	//TODO: verify this is correct

	SET_SIGN(value);
    SET_OVERFLOW(0x40 & value);	/* Copy bit 6 to OVERFLOW flag. */
    SET_ZERO(value & registers->acc);
}
#include "incdec.h"
#include "../cpu.h"
#include "../memory.h"

inline void ins_inc(uint16_t address) {
	uint8_t val = (fetch(address) + 1) & 0xff;
    SET_SIGN(val);
    SET_ZERO(val);
    store(address, val);
}

inline void ins_inx() {
	uint8_t val = (registers->x + 1) & 0xff;
    SET_SIGN(val);
    SET_ZERO(val);
    registers->x = val;
}

inline void ins_iny() {
	uint8_t val = (registers->y + 1) & 0xff;
    SET_SIGN(val);
    SET_ZERO(val);
    registers->y = val;
}

inline void ins_dec(uint16_t address) {
	uint8_t val = (fetch(address) - 1) & 0xff;
    SET_SIGN(val);
    SET_ZERO(val);
    store(address, val);
}

inline void ins_dex() {
	uint8_t val = (registers->x - 1) & 0xff;
    SET_SIGN(val);
    SET_ZERO(val);
    registers->x = val;
}

inline void ins_dey() {
	uint8_t val = (registers->y - 1) & 0xff;
    SET_SIGN(val);
    SET_ZERO(val);
    registers->y = val;
}
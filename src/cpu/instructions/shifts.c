#include "shifts.h"
#include "../cpu.h"
#include "../memory.h"

inline void ins_asl(uint8_t mem, uint8_t address) {
	uint8_t val = mem ? fetch(address) : registers->acc;

	SET_CARRY(val & 0x80);
	val <<= 1;
	val &= 0xff;
	SET_SIGN(val);
	SET_ZERO(val);

	if(mem) {
		store(address,val);
	} else {
		registers->acc = val;
	}
}

inline void ins_lsr(uint8_t mem, uint8_t address) {
	uint8_t val = mem ? fetch(address) : registers->acc;

	SET_CARRY(val & 0x01);
    val >>= 1;
    SET_SIGN(val);
    SET_ZERO(val);

    if(mem) {
		store(address,val);
	} else {
		registers->acc = val;
	}
}

inline void ins_rol(uint8_t mem, uint8_t address) {
	uint8_t val = mem ? fetch(address) : registers->acc;

	val <<= 1;
    if (IF_CARRY()) val |= 0x1;
    SET_CARRY(val > 0xff);
    val &= 0xff;
    SET_SIGN(val);
    SET_ZERO(val);
    
    if(mem) {
		store(address,val);
	} else {
		registers->acc = val;
	}
}

inline void ins_ror(uint8_t mem, uint8_t address) {
	uint16_t val = mem ? fetch(address) : registers->acc;

	if (IF_CARRY()) val |= 0x100;
    SET_CARRY(val & 0x01);
    val >>= 1;
    SET_SIGN(val);
    SET_ZERO(val);

    val &= 0xFF;
    if(mem) {
		store(address,val);
	} else {
		registers->acc = val;
	}
}
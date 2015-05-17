#include "branches.h"
#include "../cpu.h"

inline void ins_bcc(uint8_t skip) {
	if (!IF_CARRY()) {
		//clk += ((PC & 0xFF00) != (REL_ADDR(PC, src) & 0xFF00) ? 2 : 1);
		registers->pc = registers->pc + skip;
    }
}

inline void ins_bcs(uint8_t skip) {
	if (IF_CARRY()) {
		//handle clock
		registers->pc = registers->pc + skip;
    }
}

inline void ins_beq(uint8_t skip) {
	if (IF_ZERO()) {
		//clock
		registers->pc = registers->pc + skip;
    }
}

inline void ins_bmi(uint8_t skip) {
	if (IF_SIGN()) {
		//clock
		registers->pc = registers->pc + skip;
    }
}

inline void ins_bne(uint8_t skip) {
	if (!IF_ZERO()) {
		//clock
		registers->pc = registers->pc + skip;
    }
}

inline void ins_bpl(uint8_t skip) {
	if (!IF_SIGN()) {
		//clock
		registers->pc = registers->pc + skip;
    }
}

inline void ins_bvc(uint8_t skip) {
	if (!IF_OVERFLOW()) {
		//clock
		registers->pc = registers->pc + skip;
    }
}

inline void ins_bvs(uint8_t skip) {
	if (IF_OVERFLOW()) {
		//clock
		registers->pc = registers->pc + skip;
    }
}
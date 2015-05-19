#include "branches.h"
#include "../cpu.h"

#define TO_SIGN(x) (((x >> 7) & 1) ? ((255-x) & 0x7F)*-1: x)

inline void ins_bcc(uint8_t skip) {
	if (!IF_CARRY()) {
		//clk += ((PC & 0xFF00) != (REL_ADDR(PC, src) & 0xFF00) ? 2 : 1);
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
    } else {
    	registers->pc++;
    }
}

inline void ins_bcs(uint8_t skip) {
	if (IF_CARRY()) {
		//handle clock
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
    } else {
    	registers->pc++;
    }
}

inline void ins_beq(uint8_t skip) {
	if (IF_ZERO()) {
		//clock
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
    } else {
    	registers->pc = registers->pc+1;
    }
}

inline void ins_bmi(uint8_t skip) {
	if (IF_SIGN()) {
		//clock
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
    } else {
    	registers->pc++;
    }
}

inline void ins_bne(uint8_t skip) {
	if (!IF_ZERO()) {
		//clock
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
    } else {
    	registers->pc = registers->pc+1;
    }
}

inline void ins_bpl(uint8_t skip) {
	if (!IF_SIGN()) {
		//clock
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
		
    } else {
    	registers->pc++;
    }
}

inline void ins_bvc(uint8_t skip) {
	if (!IF_OVERFLOW()) {
		//clock
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
    } else {
    	registers->pc++;
    }
}

inline void ins_bvs(uint8_t skip) {
	if (IF_OVERFLOW()) {
		//clock
		int8_t toskip = TO_SIGN(skip);
		registers->pc = registers->pc + toskip;
    } else {
    	registers->pc++;
    }
}
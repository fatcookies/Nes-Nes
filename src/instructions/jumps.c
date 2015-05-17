#include "jumps.h"
#include "../cpu.h"
#include "../memory.h"
#include "../stack.h"

inline void ins_jmp(uint16_t address) {
	registers->pc = address;
}

inline void ins_jsr(uint16_t address) {
	registers->pc--;
    push((registers->pc >> 8) & 0xff);	/* Push return address onto the stack. */
    push(registers->pc & 0xff);
    registers->pc = address;
}

inline void ins_rts() {
	uint16_t ret = pop();
    ret += ((pop()) << 8) + 1;	/* Load return address from stack and add 1. */
    registers->pc = ret;
}
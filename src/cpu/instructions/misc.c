#include "misc.h"
#include "../cpu.h"
#include "../stack.h"
#include "../memory.h"

// todo: not sure about this
void ins_brk() {
	registers->pc++;
    push((registers->pc >> 8) & 0xff); /* Push return address onto the stack. */
    push(registers->pc & 0xff);
    SET_BREAK((1));             /* Set BFlag before pushing */
    push(*flags);
    SET_INTERRUPT((1));
    registers->pc = (fetch(0xFFFE) | (fetch(0xFFFF) << 8));
}

void ins_nop() {
	
}

void ins_rti() {
	uint16_t src = pop();
    *flags = src & 0xFF;
    src = pop();
    src |= (pop() << 8);   /* Load return address from stack. */
    registers->pc = (src);
}
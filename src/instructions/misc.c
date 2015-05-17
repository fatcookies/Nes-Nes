#include "misc.h"
#include "../cpu.h"
#include "../stack.h"

// todo: not sure about this
inline void ins_brk() {
	registers->pc++;
    push((registers->pc >> 8) & 0xff);	/* Push return address onto the stack. */
    push(registers->pc & 0xff);
    SET_BREAK((1));             /* Set BFlag before pushing */
    //push(1); // TODO: was push(StatusRegister)
    SET_INTERRUPT((1));
    registers->pc = fetch16(0xFFFE);
}

inline void ins_nop() {
	registers->pc++;
}

inline void ins_rti() {
	uint16_t src = pop();
    //SET_SR(src && 0xFF);
    src = pop();
    src |= (pop() << 8);	/* Load return address from stack. */
    registers->pc = src;
}
#include "stack.h"
#include "cpu.h"
#include "memory.h"

inline void push(uint8_t val) {
	store(registers->sp, val);
	registers->sp--;
}

inline uint8_t pop() {
	uint8_t val = fetch(registers->sp);
	registers->sp++;
	return val;
}
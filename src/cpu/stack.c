#include "stack.h"
#include "cpu.h"
#include "memory.h"

void push(uint8_t val) {
	store(registers->sp, val);
	registers->sp--;
}

uint8_t pop() {
	uint8_t val = fetch(registers->sp);
	registers->sp++;
	return val;
}
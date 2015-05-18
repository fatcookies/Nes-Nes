#include "cpu/cpu.h"
#include <stdio.h>

int main() {
	cpu_init();
	printf("pc=%u\n",registers->pc);
	return 0;
}
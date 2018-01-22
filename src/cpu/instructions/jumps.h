#ifndef _STDINT_H_
#include <stdint.h>
#endif

void ins_jmp(uint16_t address);

void ins_jsr(uint16_t address);

void ins_rts();
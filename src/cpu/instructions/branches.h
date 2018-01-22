#ifndef _STDINT_H_
#include <stdint.h>
#endif

void ins_bcc(uint8_t skip);

void ins_bcs(uint8_t skip);

void ins_beq(uint8_t skip);

void ins_bmi(uint8_t skip);

void ins_bne(uint8_t skip);

void ins_bpl(uint8_t skip);

void ins_bvc(uint8_t skip);

void ins_bvs(uint8_t skip);
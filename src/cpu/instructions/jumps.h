#ifndef _STDINT_H_
#include <stdint.h>
#endif

inline void ins_jmp(uint16_t address);

inline void ins_jsr(uint16_t address);

inline void ins_rts();
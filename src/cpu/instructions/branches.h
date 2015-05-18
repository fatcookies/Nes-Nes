#ifndef _STDINT_H_
#include <stdint.h>
#endif

inline void ins_bcc(uint8_t skip);

inline void ins_bcs(uint8_t skip);

inline void ins_beq(uint8_t skip);

inline void ins_bmi(uint8_t skip);

inline void ins_bne(uint8_t skip);

inline void ins_bpl(uint8_t skip);

inline void ins_bvc(uint8_t skip);

inline void ins_bvs(uint8_t skip);
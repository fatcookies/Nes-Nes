#ifndef _STDINT_H_
#include <stdint.h>
#endif

extern uint16_t immediate();

extern uint16_t zeropage();

extern uint16_t zeropage_x();

extern uint16_t zeropage_y();

extern uint16_t absolute();

extern uint16_t absolute_x();

extern uint16_t absolute_y();

extern uint16_t indirect();

extern uint16_t indirect_x();

extern uint16_t indirect_y();


extern uint16_t absolute_x_pages();

extern uint16_t absolute_y_pages();

extern uint16_t indirect_y_pages();
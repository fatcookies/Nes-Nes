#include <stdint.h>

typedef struct {
	/* Program Counter */
	uint16_t pc;

	/* Stack Pointer */
	uint16_t sp;

	/* Accumulator Register */
	uint8_t acc;


	/* Index Register X */
	uint8_t x;

	/* Index Register Y */
	uint8_t y;

} reg;

typedef struct {
	uint8_t carry;
	uint8_t zero;
	uint8_t interrupt;
	uint8_t dec;
	uint8_t break_cmd;
	uint8_t overflow;
	uint8_t sign;
} flag ;

reg * registers;
flag * flags;

#define combine(upper, lower) ((upper<<8) | lower)
#define IF_CARRY() (flags->carry & 0xFF)
#define SET_ZERO(x) flags->zero = (x & 0xFF)
#define SET_SIGN(x) flags->sign = ((x >> 7) & 1)
#define SET_CARRY(x) flags->carry = ((x) & 0xFF)
#define SET_OVERFLOW(x) flags->overflow = (x & 0xFF)
#define SET_BREAK(x) flags->break_cmd = x
#define SET_INTERRUPT(x) flags->interrupt = x

void cpu_init();
void reset();
inline uint8_t next();
inline uint16_t next16();
inline uint16_t fetch16(uint16_t address);

void exec();


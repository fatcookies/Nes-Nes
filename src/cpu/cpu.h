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

uint8_t *flags;
reg * registers;

#define SET_CARRY(x)     *flags |= (x ? 1 : 0)
#define SET_ZERO(x)      *flags |= (x ? 0 : 1) << 1
#define SET_INTERRUPT(x) *flags |= (x ? 1 : 0) << 2
#define SET_DEC(x)       *flags |= (x ? 1 : 0) << 3
#define SET_BREAK(x)     *flags |= (x ? 1 : 0) << 4
#define SET_OVERFLOW(x)  *flags |= (x ? 1 : 0) << 6
#define SET_SIGN(x)      *flags |= ((x >> 7) & 1) << 7

#define IF_CARRY()    ((*flags) & 1)
#define IF_ZERO()     ((*flags >> 1) & 1)
#define IF_OVERFLOW() ((*flags >> 6) & 1)
#define IF_SIGN()     ((*flags >> 7) & 1)

#define combine(upper, lower) ((upper<<8) | lower)

void cpu_init();
void reset();
inline uint8_t cpu_status();

inline uint8_t next();
inline uint16_t next16();
inline uint16_t fetch16(uint16_t address);

void exec();


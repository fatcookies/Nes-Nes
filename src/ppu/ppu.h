#ifndef _STDINT_H_
#include <stdint.h>
#endif

typedef struct {
	uint8_t control1;
	uint8_t control2;
	uint8_t status;
	uint8_t sprite_address;
	uint8_t sprite_data;

	//scroll
	uint8_t cam_position_x;
	uint8_t cam_position_y;

	uint16_t fulladdress;
	uint8_t data;

} ppu_register;

ppu_register * ppu_registers;

#define SETBIT(f,x,n)	(f ^= (-x ^ f) & (1 << n));

//status
#define TOGGLE_LSB_WRITTEN() (ppu_registers->status ^= 1 << 4)
#define SET_LSB_WRITTEN(x)    SETBIT(ppu_registers->status, (x ? 1 : 0), 4)
#define SET_SPRITE_OVRFLOW(x) SETBIT(ppu_registers->status, (x ? 1 : 0), 5)
#define SET_SPRITE0_HIT(x)    SETBIT(ppu_registers->status, (x ? 1 : 0), 6)
#define SET_VERTICAL_BLANK(x) SETBIT(ppu_registers->status, (x ? 1 : 0), 7)
#define IF_LSB_WRITTEN() ((ppu_registers->status >> 4) & 1)
#define IF_SPRITE_OVRFLOW() ((ppu_registers->status >> 5) & 1)
#define IF_SPRITE0_HIT() ((ppu_registers->status >> 6) & 1)
#define IF_VERTICAL_BLANK() ((ppu_registers->status >> 7) & 1)

//control1
#define BASE_NAMETABLE_ADDRESS()   ((ppu_registers->control1) & 3) 
#define ADDRESS_INCREMENT()        ((ppu_registers->control1 >> 4) & 2)
#define SPRITE_PATTERN_TABLE()     ((ppu_registers->control1 >> 4) & 3)
#define BACKGROUND_PATTERN_TABLE() ((ppu_registers->control1 >> 4) & 4)
#define SPRITE_SIZE()              ((ppu_registers->control1 >> 4) & 5)
#define PPU_MASTER_SELECT()        ((ppu_registers->control1 >> 4) & 6)
#define ENABLE_NMI()               ((ppu_registers->control1 >> 4) & 7)

//control2
#define GRAYSCALE()           (ppu_registers->control1 & 1)
#define BACKGROUND_LEFTMOST() ((ppu_registers->control1 >> 1) & 1)
#define SPRITES_LEFTMOST()    ((ppu_registers->control1 >> 2) & 1)
#define SHOW_BACKGROUND()     ((ppu_registers->control1 >> 3) & 1)
#define SHOW SPRITES()        ((ppu_registers->control1 >> 4) & 1)
#define EMPH_RED()            ((ppu_registers->control1 >> 5) & 1)
#define EMPH_GREEN()          ((ppu_registers->control1 >> 6) & 1)
#define EMPH_BLUE()           ((ppu_registers->control1 >> 7) & 1)


uint8_t* handle_ppu_input(uint16_t address);

uint8_t* handle_ppu_output(uint16_t address);

void ppu_init();

void ppu_exec();
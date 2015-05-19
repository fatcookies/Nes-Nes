#ifndef _STDINT_H_
#include <stdint.h>
#endif

#define PPU_MEMORY_SIZE 0x4000
#define OAM_MEMORY_SIZE 0x100

//Sprite Palette
#define SPRITE_PALETTE 0x3F10

//Image Palette
#define IMAGE_PALETTE 0x3F00

//Attribute Table 3
#define ATTRIBUTE_TABLE_3 0x2FC0

//Name Table 3 (32x30 tiles)
#define NAME_TABLE_3 0x2C00

//Attribute Table 2
#define ATTRIBUTE_TABLE_2 0x2BC0

//Name Table 2 (32x30 tiles)
#define NAME_TABLE_2 0x2800

//Attribute Table 1
#define ATTRIBUTE_TABLE_1 0x27C0

//Name Table 1 (32x30 tiles)
#define NAME_TABLE_1 0x2400

// Attribute Table 0
#define ATTRIBUTE_TABLE_0 0x23C0

// Name Table 0 (32x30 tiles)
#define NAME_TABLE_0 0x2000

//Pattern Table 1 (256x2x8, may be VROM)
#define PATTERN_TABLE_1 0x1000

//Pattern Table 0 (256x2x8, may be VROM)
#define PATTERN_TABLE_0 0x0000

uint8_t* ppu_mem;
uint8_t* ppu_oam;

void ppumem_init();

uint8_t ppu_fetch(uint16_t address);

uint16_t ppu_store(uint16_t address, uint8_t value);

uint8_t ppu_oam_fetch(uint8_t address);

uint8_t ppu_oam_store(uint8_t address, uint8_t value);

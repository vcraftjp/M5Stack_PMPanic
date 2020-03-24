#pragma once
#include <Arduino.h>

extern const uint8_t bg_rwanda1[];
extern const uint8_t boy_idling_fine[];
extern const uint8_t girl_idling_fine[];
extern const uint8_t boy_walk_fine[];
extern const uint8_t girl_walk_fine[];
extern const uint8_t boy_idling_sick[];
extern const uint8_t girl_idling_sick[];
extern const uint8_t boy_walk_sick[];
extern const uint8_t girl_walk_sick[];
extern const uint8_t tears[];
extern const uint8_t font_36[];
extern const uint32_t bg_rwanda1_pal[];

#define BG_COUNT 1
#define SPRITE_COUNT 8
#define EFFECT_COUNT 1
#define FONT_COUNT 1
#define SPRITE_MIRROR true
#define IS_RLE true

const uint8_t *bg_images[] = { bg_rwanda1 };

const uint32_t *bg_palettes[] = { bg_rwanda1_pal };

const uint8_t bg_palette_counts[] = { 15 };

const uint8_t *sprite_images[] = { boy_idling_fine, girl_idling_fine, boy_walk_fine, girl_walk_fine, boy_idling_sick, girl_idling_sick, boy_walk_sick, girl_walk_sick };

const uint8_t *effect_images[] = { tears };

const uint8_t *font_images[] = { font_36 };

struct SpriteHeader {
	uint8_t width;
	uint8_t height;
	uint8_t count;
	uint8_t pivotX;
	uint8_t pivotY;
};
const SpriteHeader sprite_headers[] = {
	{ 93, 134, 11, 0, 0 },
	{ 93, 134, 11, 0, 0 },
	{ 103, 132, 9, 0, 0 },
	{ 104, 132, 9, 0, 0 },
	{ 69, 132, 11, 0, 0 },
	{ 69, 131, 11, 0, 0 },
	{ 87, 136, 9, 0, 0 },
	{ 85, 133, 9, 0, 0 },
};
const uint32_t sprite_frame_offsets[8][11] {
	{ 0, 3640, 7271, 10844, 14416, 17988, 21560, 25182, 28804, 32457, 36110, },
	{ 0, 3741, 7475, 11138, 14802, 18466, 22130, 25833, 29536, 33279, 37022, },
	{ 0, 3627, 7178, 10312, 13243, 16832, 20362, 23412, 26631, 0, 0, },
	{ 0, 3751, 7410, 10664, 13708, 17398, 21044, 24188, 27523, 0, 0, },
	{ 0, 3384, 6777, 10149, 13534, 16919, 20304, 23700, 27096, 30516, 33936, },
	{ 0, 3506, 7012, 10481, 13958, 17435, 20912, 24409, 27906, 31428, 34950, },
	{ 0, 3348, 6633, 9752, 12727, 16084, 19466, 22593, 25518, 0, 0, },
	{ 0, 3423, 6784, 9992, 13073, 16529, 19995, 23221, 26243, 0, 0, },
};

const uint32_t sprite0_pal[] = {
	0x000000,0x000000,0x19E519,0x19B0FE,0x1B0F10,0x392024,0xBC0739,0x424668,0x5E759D,0x3991DA,0x137440,0x09351C,0x25C352,0x5E3232,0xF4F4F4,0x844646,
};

const uint32_t sprite1_pal[] = {
	0x000000,0x000000,0xFF1962,0xFA6ECB,0x5D3036,0x431F25,0x1E0E11,0x2F141B,0x0C0507,0xA30E3C,0xE01556,0x7A4569,0xAD5491,0xD14EB0,0xF4F4F4,0x844646,
};

const uint8_t sprite_palette_indices[] = { 0, 1, 0, 1, 0, 1, 0, 1 };
const uint32_t *sprite_palettes[] = { sprite0_pal, sprite1_pal };
const uint8_t sprite_palette_counts[] = { 16, 16 };

struct EffectHeader {
	uint8_t width;
	uint8_t height;
	uint8_t count;
};
const EffectHeader effect_headers[] = {
	{ 6, 11, 1 },
};
const uint32_t Effect_frame_offsets[1][1] {
	{ 0, },
};

struct FontHeader {
	uint8_t width;
	uint8_t height;
	uint8_t count;
	uint8_t spacing;
};
const FontHeader font_headers[] = {
	{ 32, 36, 11, 24 },
};
const uint32_t font_frame_offsets[1][11] {
	{ 0, 461, 848, 1213, 1611, 2008, 2425, 2856, 3216, 3637, 4069, },
};

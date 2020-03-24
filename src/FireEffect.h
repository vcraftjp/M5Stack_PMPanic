//
// FireEffect.h
//
#pragma once

#include <M5Stack.h>

#define FIRE_PALETTE_COUNT 16
extern const uint32_t firePalettes[FIRE_PALETTE_COUNT];

class FireEffect {
public:
	void init(int16_t width, int16_t height);
	void update(int power = 5, int maxPower = 10);
	void clear();

	uint8_t* getImage() { return image; }

private:
	int16_t width;
	int16_t height;
	uint8_t* buffer;
	uint8_t* image;
};
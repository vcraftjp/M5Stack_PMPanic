//
// FireEffect.cpp
// https://github.com/leonardo-ono/JavaOldFireEffectTest/blob/master/src/oldfireeffecttest/OldFireEffectTest.java
//

#include "FireEffect.h"

#define MAX_VALUE 255

const uint32_t firePalettes[FIRE_PALETTE_COUNT] = {
//	0x0000, 0x3000, 0x6000, 0x9800, 0xC800, 0xF800, 0xF980, 0xFB20,	0xFCC0, 0xFE60, 0xFFE0, 0xFFE6, 0xFFEC, 0xFFF3, 0xFFF9, 0xFFFF
	0x000000, 0x330000, 0x660000, 0x990000, 0xCC0000, 0xFF0000, 0xFF3300, 0xFF6600,
	0xFF9900, 0xFFCC00, 0xFFFF00, 0xFFFF33, 0xFFFF66, 0xFFFF99, 0xFFFFCC, 0xFFFFFF
};

void FireEffect::init(int16_t _width, int16_t _height) {
	width = _width;
	height = _height;

	buffer = (uint8_t*)calloc(width * (height + 2), sizeof(uint8_t));
	image = (uint8_t*)calloc(width * height, sizeof(uint8_t));
}

void FireEffect::clear() {
	memset(buffer, 0, width * (height + 2));
}

void FireEffect::update(int power, int maxPower) {
	for (int x = 0; x < width; x++) {
		buffer[x + width * height] = random(maxPower) > power ? 0 : MAX_VALUE;
	}

	for (int y = 5; y < height; y++) {
		for (int x = 2; x < width - 2; x++) {
			buffer[x + width * y] =
				(int) ((int) ( (buffer[x + width * y]
				+ buffer[x + width * (y + 1)]
				+ buffer[(x - 1) + width * (y + 1)]
				+ buffer[(x + 1) + width * (y + 1)]
				+ buffer[x + width * (y + 2)]
					) / 5.045f ) * 1.01f);
		}
	}

	int size = width * height;
	for (int i = 0; i < size; i++) {
		int n = buffer[i] / 8;
		if (n >= FIRE_PALETTE_COUNT) {
			n = FIRE_PALETTE_COUNT - 1;
		}
		image[i] = n;
	}
}
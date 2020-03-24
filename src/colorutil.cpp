//
// colorutil.cpp
//

#include "colorutil.h"
#include "mydefs.h"

uint32_t hsvToRGB(int h, int s, int v, uint8_t *pRGB) {
	uint8_t _max = v * 255 / MAX_SV;
	uint8_t _min = _max - (s * _max / MAX_SV);
	uint8_t d = _max - _min;
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;

	h %= 360;
	switch (h / 60) {
		case 0:
			r = _max;
			g = h * d / 60 + _min;
			b = _min;
			break;
		case 1:
			r = (120 - h) * d / 60 + _min;
			g = _max;
			b = _min;
			break;
		case 2:
			r = _min;
			g = _max;
			b = (h - 120) * d / 60 + _min;
			break;
		case 3:
			r = _min;
			g = (240 - h) * d / 60 + _min;
			b = _max;
			break;
		case 4:
			r =  (h - 240) * d / 60 + _min;
			g = _min;
			b = _max;
			break;
		case 5:
			r = _max;
			g = _min;
			b = (360 - h) * d / 60 + _min;
			break;
	}
	if (pRGB) {
		pRGB[0] = r;
		pRGB[1] = g;
		pRGB[2] = b;
	}
	return rgbToColor32(r, g, b);
}

uint32_t hsvToRGB(int16_t *pHSV, uint8_t *pRGB) {
	return hsvToRGB((int)pHSV[0], (int)pHSV[1], (int)pHSV[2], pRGB);
}

void rgbToHSV(uint32_t color, int16_t *pHSV) {
	uint8_t r = getRed(color);
	uint8_t g = getGreen(color);
	uint8_t b = getBlue(color);

	uint8_t _max = max(max(r, g), b);
	uint8_t _min = min(min(r, g), b);

	int16_t h = 0;
	int16_t s = 0;
	int16_t v = _max;
	int32_t d = _max - _min;

	if (_max > 0) {
		s = (int16_t)(d * MAX_SV / _max);
		if (d > 0) {
			if (_max == r) {
				h = ((int16_t)(g - b) * 60) / d;
			} else if (_max == g) {
				h = ((int16_t)(b - r) * 60) / d + 120;
			} else {
				h = ((int16_t)(r - g) * 60) / d + 240;
			}
		}
		if (h < 0) {
			h += 360;
		} else if (h > 360) {
			h -= 360;
		}
	}
	pHSV[0] = h;
	pHSV[1] = s;
	pHSV[2] = v;
	return;
}

uint32_t rgbToColor32(uint8_t r, uint8_t g, uint8_t b) {
	return (uint32_t)r << 16 | (uint32_t)g << 8 | b;
}

uint16_t rgbToColor16(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

uint16_t color32To16(uint32_t color) {
	return rgbToColor16((color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);

}

void color32ToRGB(uint32_t color, uint8_t *pRGB) {
	if (pRGB) {
		pRGB[0] = getRed(color);
		pRGB[1] = getGreen(color);
		pRGB[2] = getBlue(color);
	}
}


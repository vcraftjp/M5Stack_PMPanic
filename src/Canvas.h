//
// Canvas.h
// 8bpp indexed color frame buffer drawer
//
#pragma once

#include <M5Stack.h>
#include "DMADrawer.h" // https://github.com/lovyan03/M5Stack_LovyanToyBox/tree/master/LovyanToyBox/src

class Canvas {
public:
	Canvas(bool _isRLE = true, bool _isMT = true);
	void createFrameBuffer(int16_t width, int16_t height, int16_t dmaPartition = 6);
	void *setColorDepth(int8_t b) { return NULL; } // 8bpp only
	void setPalette(const uint16_t *palette, int count, int offset = 0);
	void setPalette(const uint32_t *palette, int count, int offset = 0);
	void setPalette(uint8_t pal, uint32_t c);
	void setPalette(uint8_t pal, uint16_t c) {
		palette[pal] = (c << 8 | c >> 8); // swap byte;
	}
	void setPalette2(const uint32_t *palette, int count, int offset, int hue, int sPlus, int vPlus = 0);
	uint16_t getPalette(uint8_t pal) { return palette[pal]; }

	void fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t pal, bool blend = false);
	void fill(uint8_t pal);
	void drawBitmap(int32_t x, int32_t y, int32_t w, int32_t h, const uint8_t *bitmap
		, uint8_t palOffset = 0,  bool isTransparent = false, bool mirror = false);
	void drawBitmap(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t *bitmap, uint8_t palOffset = 0);
	void drawBitmap(const uint8_t *bitmap, uint8_t palOffset = 0);
//	void drawBitmap(uint8_t *bitmap);
	void blendBitmap(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t *bitmap, uint8_t dimmer
		, uint8_t palOffset, uint8_t palWidth, uint8_t depth, uint8_t overlayPal);

	void drawNumber(int32_t x, int32_t y, int number, int columns, const uint8_t *font, const uint32_t *fontFrameOffsets,
		uint8_t fontWidth, uint8_t fontHeight, uint8_t fontSpacing);

	void flush();
	void beginMT();
	void endMT();

	int16_t width;
	int16_t height;
	bool isIPS;

private:
	uint8_t *buffer;
	uint16_t palette[256];

	const uint8_t *decodeRLE(const uint8_t *p, int16_t len);
	bool isRLE;
	uint8_t *rleBuffer;
	int16_t rleBufferSize;

	DMADrawer dma;
	int16_t partition;
	int16_t dmaHeight;

	bool isMT;
	volatile bool isRunning;
	volatile bool isReady;
	volatile int dmaFrame;
	void _flush();
	static void taskDraw(void* arg);

	static uint32_t adjustIPSGamma(uint32_t c, float gammaS = 0.5f, float gammaV = 2.5f);
};

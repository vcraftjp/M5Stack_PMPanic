//
// Canvas.cpp
//

#include "Canvas.h"
#include "colorutil.h"

Canvas::Canvas(bool _isRLE, bool _isMT) {
	isRLE = _isRLE;
	isMT = _isMT;
	rleBuffer = NULL;
	rleBufferSize = 0;
}

void Canvas::createFrameBuffer(int16_t _width, int16_t _height, int16_t dmaPartition) {
	width = _width;
	height = _height;
    buffer = (uint8_t*)calloc(width * height, sizeof(uint8_t));

	partition = dmaPartition;
	dmaHeight = height / dmaPartition;
	dma.setup(width * dmaHeight);

	beginMT();
}

void Canvas::setPalette(const uint16_t *p, int count, int offset) {
	for (int i = 0; i < count; i++) {
		setPalette(i + offset, *p++);
	}
}

void Canvas::setPalette(const uint32_t *p, int count, int offset) {
	for (int i = 0; i < count; i++) {
		setPalette(i + offset, *p++);
	}
}

void Canvas::setPalette(uint8_t pal, uint32_t c) {
	if (isIPS) {
		c = adjustIPSGamma(c);
	}
	setPalette(pal, color32To16(c));
}

void Canvas::setPalette2(const uint32_t *p, int count, int offset, int hue, int sPlus, int vPlus) {
	int16_t hsv[3];
	for (int i = 0; i < count; i++) {
		rgbToHSV(*p++, hsv);
		hsv[0] = hue;
		hsv[1] = min(hsv[1] + sPlus, MAX_SV);
		hsv[2] = max(hsv[2] + vPlus, 0);
		setPalette(i + offset, hsvToRGB(hsv));
	}
}


void Canvas::fillRect(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t pal, bool blend) {
	if (x < 0) { w += x; x = 0; }

	if ((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;
	if ((x + w) > width)  w = width  - x;
	if ((y + h) > height) h = height - y;
	if ((w < 1) || (h < 1)) return;

	int32_t yp = width * y + x;

	if (!blend) {
		while (h--) {
			memset(buffer + yp, pal, w);
			yp += width;
		}
	} else {
		while (h--) {
			uint8_t *p = buffer + yp;
			for (int i = 0; i < w; i++) {
				*p++ |= pal;
			}
			yp += width;
		}
	}
}

void Canvas::fill(uint8_t pal) {
    memset(buffer, pal, width * height);
}

void Canvas::drawBitmap(int32_t x0, int32_t y0, int32_t w0, int32_t h0, const uint8_t *bitmap, uint8_t palOffset, bool isTransparent, bool mirror) {
	int x = x0, y = y0, w = w0, h = h0;
	int p_offset = 0;

	if (x < 0) {
		p_offset = mirror ? x : -x;
		w += x;
		x = 0;
	}
	if ((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;
	if ((x + w) > width) {
		w = width - x;
	}
	if ((y + h) > height) {
		h = height - y;
	}
	if ((w < 1) || (h < 1)) return;

	int q_offset = width * y + x;

	if (isRLE) {
		decodeRLE(bitmap, w0 * h0);
	}
	while (h--) {
		uint8_t *q = buffer + q_offset;
		if (!isRLE) {
			const uint8_t *p = bitmap + p_offset;
			if (!mirror) {
				for (int i = 0; i < w; i++) {
					uint8_t b = pgm_read_byte(p++);
					if (b == 0 && isTransparent) {
						q++;
					} else {
						*q++ = b + palOffset;
					}
				}
			} else {
				p += w0;
				for (int i = 0; i < w; i++) {
					uint8_t b = pgm_read_byte(--p);
					if (b == 0 && isTransparent) {
						q++;
					} else {
						*q++ = b + palOffset;
					}
				}
			}
		} else { // isRLE
			uint8_t *p = rleBuffer + p_offset;
			if (!mirror) {
				for (int i = 0; i < w; i++) {
					uint8_t b = *p++;
					if (b == 0 && isTransparent) {
						q++;
					} else {
						*q++ = b + palOffset;
					}
				}
			} else {
				p += w0;
				for (int i = 0; i < w; i++) {
					uint8_t b = *(--p);
					if (b == 0 && isTransparent) {
						q++;
					} else {
						*q++ = b + palOffset;
					}
				}
			}
		}
		p_offset += w0;
		q_offset += width;
	}
}

void Canvas::drawBitmap(int32_t x, int32_t y, int32_t w, int32_t h, uint8_t *bitmap, uint8_t palOffset) {
	uint8_t *p = bitmap;
	int q_offset = width * y + x;
	while (h--) {
		uint8_t *q = buffer + q_offset;
		for (int i = 0; i < w; i++) {
			uint8_t b = *p++;
			if (b) {
				*q++ = b + palOffset;
			} else {
				q++;
			}
		}
		q_offset += width;
	}
}

void Canvas::drawBitmap(const uint8_t *bitmap, uint8_t palOffset) {
	const uint32_t *p = (const uint32_t *)bitmap;
	uint32_t *q = (uint32_t *)buffer;
	uint32_t dpal = palOffset | ((uint32_t)palOffset) << 8 | ((uint32_t)palOffset) << 16 | ((uint32_t)palOffset) << 24;
	for (int n = 0; n < partition; n++) {
		if (isMT) {
			while (n >= dmaFrame) taskYIELD();
		}
		if (!isRLE) {
			int len = width * dmaHeight / sizeof(uint32_t);
			for (int i = 0; i < len; i++) {
				*q++ = pgm_read_dword(p++) + dpal;
			}
		} else {
			for (int y = 0; y < dmaHeight; y++) {
				p = (const uint32_t*)decodeRLE((const uint8_t*)p, width);
				uint32_t *p1 = (uint32_t*)rleBuffer;
				int len = width / sizeof(uint32_t);
				for (int i = 0; i < len; i++) {
					*q++ = *p1++ + dpal;
				}
			}
		}
	}
}

// void Canvas::drawBitmap(uint8_t *bitmap) {
// 	memcpy(buffer, bitmap, width * height);
// }

// for draw particles
void Canvas::blendBitmap(int32_t x0, int32_t y0, int32_t w0, int32_t h0, uint8_t *bitmap, uint8_t dimmer
						, uint8_t palOffset, uint8_t palWidth, uint8_t depth, uint8_t overlayPal) {
	int x = x0, y = y0, w = w0, h = h0;
	int p_offset = 0;

	if (x < 0) {
		p_offset = -x;
		w += x;
		x = 0;
	}
	if ((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;
	if ((x + w) > width) {
		w = width - x;
	}
	if ((y + h) > height) {
		h = height - y;
	}
	if ((w < 1) || (h < 1)) return;

	int q_offset = width * y + x;

	while (h--) {
		uint8_t *q = buffer + q_offset;
		const uint8_t *p = bitmap + p_offset;
		for (int i = 0; i < w; i++) {
			uint8_t b = *p++;
			b = max(b - dimmer, 0);
			if (b == 0) {
				q++;
			} else if (b == depth) {
				*q++ = overlayPal;
			} else {
				uint8_t d = *q;
				if (d >= palOffset && d < palWidth) {
					*q++ = d + b * palWidth;
				} else {
					q++;
				}
			}
		}
		p_offset += w0;
		q_offset += width;
	}
}


void Canvas::drawNumber(int32_t x, int32_t y, int number, int columns, const uint8_t *font, const uint32_t *fontFrameOffsets,
						uint8_t fontWidth, uint8_t fontHeight, uint8_t fontSpacing) {
	int m = 1;
	for (int i = 0; i < columns - 1; i++) {
		m *= 10;
	}
	for (int i = 0; i < columns; i++) {
		int n = number / m;
		number %= m;
		int offset = fontFrameOffsets ? fontFrameOffsets[n] : fontWidth * fontHeight * n;
		const uint8_t *p = font + offset;
		drawBitmap(x, y, fontWidth, fontHeight, p, 0, true);
		x += fontSpacing;
		m /= 10;
	}
}

const uint8_t *Canvas::decodeRLE(const uint8_t *p, int16_t len) {
	if (len > rleBufferSize) {
		if (rleBuffer) {
			free(rleBuffer);
		}
		rleBuffer = (uint8_t *)malloc(len);
	}
	uint8_t *q = rleBuffer;
	uint8_t *qEnd = q + len;
	while (q < qEnd) {
		uint8_t b = *p++;
		uint8_t c = b & 0x7F;
		if ((b & 0x80) != 0) {
			b = *p++;
			for (int16_t j = 0; j < c + 1; j++) {
				*q++ = b;
			}
		} else {
			for (int16_t j = 0; j < c + 1; j++) {
				*q++ = *p++;
			}
		}
	}
	return p;
}

void Canvas::flush() {
	if (isMT) {
		while (dmaFrame < partition) taskYIELD();
		isReady = true;
	} else {
		_flush();
	}
}

void Canvas::_flush() {
	uint8_t *p = buffer;
	for (int n = 0; n < partition; n++) {
		dmaFrame = n;
		uint16_t *q = dma.getNextBuffer();
		int len = width * dmaHeight;
		while (len--) {
			*q++ =  palette[*p++];
		}
		dma.draw(0, dmaHeight * n, width, dmaHeight);
	}
	dmaFrame = partition;
}

void Canvas::taskDraw(void* arg) {
	Canvas* me = (Canvas*)arg;
	while (me->isRunning) {
		if (me->isReady) {
			me->isReady = false;
			((Canvas*)arg)->_flush();
		} else {
			taskYIELD();
		}
	}
	vTaskDelete(NULL);
}

void Canvas::beginMT() {
	if (isMT) {
		isReady = false;
		dmaFrame = partition;

		isRunning = true;
		xTaskCreatePinnedToCore(taskDraw, "taskDraw", 1024, this, 1, NULL, 0);
	}
}

void Canvas::endMT() {
	if (isMT) {
		isRunning = false;
	}
}

uint32_t Canvas::adjustIPSGamma(uint32_t c, float gammaS, float gammaV) {
	int16_t hsv[3];

	rgbToHSV(c, hsv);
	hsv[1] = (uint16_t)(pow((float)hsv[1] / 255.f, gammaS) * 255.f);
	hsv[2] = (uint16_t)(pow((float)hsv[2] / 255.f, gammaV) * 255.f);
	return hsvToRGB(hsv);
}

//
// colorutil.h
//
#pragma once

#include <stdint.h>
#include <stdlib.h>

inline uint8_t getRed(uint32_t color) { return (uint8_t)((color >> 16) & 0xFF); }
inline uint8_t getGreen(uint32_t color) { return (uint8_t)((color >> 8) & 0xFF); }
inline uint8_t getBlue(uint32_t color) { return (uint8_t)(color & 0xFF); }

uint32_t rgbToColor32(uint8_t r, uint8_t g, uint8_t b);
uint16_t rgbToColor16(uint8_t r, uint8_t g, uint8_t b);
uint16_t color32To16(uint32_t color);
void color32ToRGB(uint32_t color, uint8_t *pRGB);

#define MAX_SV 255
uint32_t hsvToRGB(int16_t h, int16_t s, int16_t v, uint8_t *pRGB = NULL);
uint32_t hsvToRGB(int16_t *pHSV, uint8_t *pRGB = NULL);
void rgbToHSV(uint32_t color, int16_t *pHSV);

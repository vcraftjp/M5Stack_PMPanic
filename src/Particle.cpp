//
// Particle.cpp (PM2.5 ver.)
//
#include "Particle.h"

#define MIN_SPEED 1
#define MAX_SPEED 3

static float canvasWidth;
static float canvasHeight;
uint8_t* particleImage;
float paletteTable[PARTICLE_DIMMER_STEP] = { 1.0f, 0.8f, 0.5f, 0.3f };

uint8_t* createImage(int size) {
	int r = size / 2;
	uint8_t *img = (uint8_t*)calloc(size * size, sizeof(uint8_t));
	uint8_t *q = img;
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			float d = sqrtf(float((x - r) * (x - r) + (y - r) * (y - r))) / (float)r;
			int i = 0;
			for (; i < PARTICLE_DIMMER_STEP; i++) {
				if (d >= paletteTable[i]) break;
			}
			*q++ = (uint8_t)i;
			Serial.printf("%d,", i);
		}
		Serial.println("");
	}
	return img;
}

void Particle::init(int16_t w, int16_t h) {
	canvasWidth = w;
	canvasHeight = h;
	particleImage = createImage(PARTICLE_SIZE);
}

uint8_t* Particle::getImage() {
	return particleImage;
}

Particle::Particle() {
	refresh();
}

void Particle::refresh() {
	x = random(canvasWidth);
	y = random(canvasHeight);
	float v = random(MAX_SPEED - MIN_SPEED + 1) + MIN_SPEED;
	float a = random(360) * 3.1416f / 180.0f;
	vx = v * sin(a);
	vy = v * cos(a);

	dimmer = random(PARTICLE_DIMMER_STEP);
	isShow = true;
}

void Particle::update() {
	x += vx;
	y += vy;
	if (x < -PARTICLE_SIZE || x >= canvasWidth + PARTICLE_SIZE || y < -PARTICLE_SIZE || y >= canvasHeight + PARTICLE_SIZE) {
		refresh();
	}
}

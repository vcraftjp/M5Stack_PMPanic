//
// Particle.h (PM2.5 ver.)
//
#pragma once

#include <Arduino.h>

#define PARTICLE_SIZE 16
#define PARTICLE_DIMMER_STEP 4

//
// Particle class
//
class Particle {
public:

	Particle();

	void refresh();
	void setPosition(float _x, float _y) { x = _x; y = _y; }
	void setVelocity(float _vx, float _vy) { vx = _vx; vy = _vy; }
	void setAccel(float accelX, float accelY) { vx += accelX; vy += accelY; }
	int16_t getX() { return (int16_t)x; }
	int16_t getY() { return (int16_t)y; }

	void update();

	static void init(int16_t w, int16_t h);
	static uint8_t* getImage();

public:
	uint8_t dimmer;
	bool isShow;

private:
	float x;
	float y;
	float vx;
	float vy;
};

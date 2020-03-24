//
// KidSprite.h
//
#pragma once

#include <Arduino.h>

enum KidMode { KID_IDLE, KID_WALK };

struct Tear {
	int16_t dx;
	int16_t dy;
};

#define MAX_TEARS 8

class KidSprite {
public:
	KidSprite();

	void init(int x, int y, int lcdWidth);
	int getSpriteIndex();
	bool update(int appFPS, int frameCount);
	void toggleSprite() { isGirl = !isGirl; }
	void setSickLevel(int sick);

	bool isGirl;
	bool isSick;
	int x;
	int y;
	bool mirror;
	KidMode mode;
	int frame;

	Tear tears[MAX_TEARS];
	bool isTearDropped;

private:
	int lcdWidth;
	int dx;
	int sick;
	int _frame; // for blinking
	int elapse;
	int frameSteps;
	int tearStep;
	int tearsCount;
	bool tearDropped;

	void moveKid(bool center);
	void updateTears();
	void clearTears();
	void flipTears();
	void addTear();
};
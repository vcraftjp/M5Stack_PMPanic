//
// KidSprite.cpp
//

#include "KidSprite.h"

#define SPRITE_FPS 10
#define SICK_LEVEL 1
#define KID_BLINK_RATE 5
#define WALKING_STEP 4
#define ELAPSE_BASE 20
#define TEAR_DROP_DELAY 8
#define TEAR_DROP_DY 2
#define TEAR_MAX_Y 100

int8_t kidBlinkFrame[] = { 2, 1 };

KidSprite::KidSprite() {
	isGirl = false;
	_frame = 0;
	frameSteps = 0;
	mode = KID_IDLE;
	elapse = ELAPSE_BASE;

	clearTears();
}

void KidSprite::init(int _x, int _y, int _lcdWidth) {
	x = _x;
	y = _y;
	lcdWidth = _lcdWidth;
}

int KidSprite::getSpriteIndex() {
	return (mode * 2) + (isGirl ? 1 : 0) + (isSick ? 4 : 0);
}

void KidSprite::setSickLevel(int _sick) {
	if (sick != _sick) {
		sick = _sick;
		isSick = (sick > SICK_LEVEL);
		clearTears();
	}
}

void KidSprite::moveKid(bool center) {
	int prevMode = mode;
	bool prevMirror = mirror;
	if (x <= 0) {
		dx = WALKING_STEP;
		mirror = false;
	} else if (x >= lcdWidth) {
		dx = -WALKING_STEP;
		mirror = true;
	} else {
		if (dx) {
			if (center) {
				dx = 0;
			} else {
				dx = (random(0, 3) - 1) * WALKING_STEP;
			}
		} else {
			dx = random(0, 2) ? WALKING_STEP : -WALKING_STEP;
		}
		if (dx > 0) {
			mirror = false;
			mode = KID_WALK;
		} else if (dx < 0) {
			mirror = true;
			mode = KID_WALK;
		} else {
			mode = KID_IDLE;
		}
	}
	x += dx;
	if (elapse <= 0) {
		elapse = random(1, 5) * ELAPSE_BASE;
	}
	if (prevMode != mode) {
		clearTears();
	} else if (prevMirror != mirror) {
		flipTears();
	}
	Serial.printf("kid: X=%d Dx=%d mirror=%d elapse=%d\r\n", x, dx, mirror, elapse);
}

bool KidSprite::update(int appFPS, int frameCount) {
	int step = SPRITE_FPS - sick;
	bool r = false;
	if ((frameSteps += step) >= appFPS) {
		frameSteps = 0;

		if (++_frame >= frameCount - 1) {
			_frame = 0;
		}
		frame = _frame;
		if (_frame == kidBlinkFrame[mode]) {
			if (random(KID_BLINK_RATE) == 0) {
				frame = frameCount - 1; // blink frame
			}
		}
		elapse--;
		if (x <= 0 || x >= lcdWidth) {
			moveKid(false);
		} else if(elapse <= 0 && x >= lcdWidth / 2 - WALKING_STEP && x <= lcdWidth / 2 + WALKING_STEP && random(2) == 0) {
			moveKid(true);
		} else {
			x += dx;
		}
		r = true;
	}
	updateTears();
	return r;
}

void KidSprite::updateTears() {
	isTearDropped = false;
	int maxTears = (sick - SICK_LEVEL) * 2;
	if (maxTears < 0) {
		maxTears = 0;
	}
	if (tearsCount < maxTears) {
		if (tearsCount == 0 || ++tearStep >= TEAR_DROP_DELAY) {
			if (random(2) == 0) {
				tearStep = 0;
				addTear();
			}
		}
	}
	for (int i = 0; i < MAX_TEARS; i++) {
		Tear& tear = tears[i];
		if (tear.dx != 0) {
			tear.dy += TEAR_DROP_DY;
			if (tear.dy >= TEAR_MAX_Y) {
				tear.dx = 0;
				if (!tearDropped) {
					tearDropped = true;
				} else {
					tearDropped = false;
					tearsCount -= 2;
				}
			}
		}
	}
}

void KidSprite::clearTears() {
	memset(tears, 0, sizeof(tears));
	tearStep = 0;
	tearsCount = 0;
	tearDropped = false;
}

void KidSprite::flipTears() {
	for (int i = 0; i < MAX_TEARS; i++) {
		Tear& tear = tears[i];
		if (tear.dx != 0) {
			tear.dx = -tear.dx;
		}
	}
}

void KidSprite::addTear() {
	if (tearsCount >= MAX_TEARS) return;
	tearsCount++;
	isTearDropped = true;
	for (int i = 0; i < MAX_TEARS; i++) {
		if (tears[i].dx == 0) {
			bool right = (i & 1) == 0;
			if (right && tears[i + 1].dx == 0 && random(2) == 0) {
				i++;
				right = false;
			}
			if (mode == KID_IDLE) {
				tears[i].dx = right ? 13 : -8;
				tears[i].dy = 28;
			} else { // KID_WALK
				int dx = mirror ? 8 : 0;
				tears[i].dx = (right ^ mirror) ? (16 - dx) : (-5 - dx);
				tears[i].dy = right ? 40 : 32;
			}
			Serial.printf("tear #%d: dx=%d dy=%d right(%d) mirror(%d)\r\n", i, tears[i].dx, tears[i].dy, right, mirror);
			break;
		}
	}
}

//
// PM2.5 Panic app
//

#include <M5Stack.h>
#include <M5StackUpdater.h>
#include <Preferences.h>

#include "mydefs.h"
#include "Canvas.h"
#include "Audio.h"
#include "FPS.h"
#include "colorutil.h"
#include "Particle.h"
#include "FireEffect.h"
#include "PMSensor.h"
#include "KidSprite.h"

#include "images/images.h"
#include "sounds/sounds.h"

#define PAL_SYSTEM_OFFSET 0
#define PAL_SYSTEM_COUNT 16
#define PAL_FIRE_OFFSET 16
#define PAL_FIRE_COUNT 16
#define PAL_SPRITE_OFFSET 32
#define PAL_SPRITE_COUNT 16
#define PAL_BG_OFFSET 48
#define PAL_BG_COUNT 16
// palette 64...255 for blend particles (64x3)
#define PAL_SLOT_SIZE 64
#define PAL_SLOT_COUNT 4
#define PAL_TEAR 8

#define APP_FPS 30

#define SCORE_X 240
#define SCORE_Y 4

#define MAX_PARTICLES 32
#define PAL_PARTICLE 4
#define TFT_PARTICLE TFT_BLACK
//#define TFT_PARTICLE TFT_LIGHTGREY

#define FIRE_X 36
#define FIRE_Y 138
#define FIRE_WIDTH 58
#define FIRE_HEIGHT 64
#define FIRE_MAX_POWER 32

#define RETURN_TO_SENSING (60 * 1000)

enum AppMode { APPMODE_ANIM, APPMODE_INFO, APPMODE_COUNT };
int appMode = APPMODE_ANIM;

Canvas canvas(IS_RLE);

int16_t lcdWidth;
int16_t lcdHeight;

Preferences prefs;

PMSensor pmSensor;
unsigned long sensorTick;
unsigned long pmLevelChangedTick;

int bgIndex;
int pmLevel;
int pmStep;
int16_t hueValues[PMLEVEL_COUNT] = { -1, 60, 30, 0, 270, 350 };
uint16_t scoreColors[PMLEVEL_COUNT] = { TFT_GREEN, TFT_YELLOW, TFT_ORANGE, TFT_RED, TFT_PURPLE, TFT_MAROON };

Particle *particles[MAX_PARTICLES];
uint8_t particleCounts[PMLEVEL_COUNT] = { 0, 4, 8, 12, 24, 32 };

KidSprite kid;

FireEffect fireEffect;

Audio audio;

FPS fps;

//
// Preferences
//
#define PREFS_NAME "PMPanic-cfg"
#define PKEY_MUTE "mute"
#define PKEY_GIRL "girl"

bool prefsBegin() {
	return !prefs.begin(PREFS_NAME);
}

bool prefsPutBool(const char* key, const bool value) {
	if (prefsBegin()) {
		prefs.putBool(key, value);
		prefs.end();
		return true;
	}
	return false;
}

bool prefsPutUChar(const char* key, const uint8_t value) {
	if (prefsBegin()) {
		prefs.putUChar(key, value);
		prefs.end();
		return true;
	}
	return false;
}

//
// draw functions
//
void setPaletteForBlend(const uint32_t* palette, int palCount, int palOffset, int hue = -1) {
	int16_t hsv[3];
	for (int i = 1; i < PAL_SLOT_COUNT; i++) {
		for (int j = 0; j < palCount; j++) {
			rgbToHSV(*(palette + j),hsv);
			if (hue != -1) {
				hsv[0] = hue;
				hsv[1] = min(hsv[1] + 60, MAX_SV);
			}
#if (TFT_PARTICLE == TFT_BLACK)
			hsv[2] = min(hsv[2], 192 * (PAL_SLOT_COUNT - i) / PAL_SLOT_COUNT);
#else
			hsv[1] = hsv[1] * (PAL_SLOT_COUNT - i) / (PAL_SLOT_COUNT + 1);
			hsv[2] = max(hsv[2], 192 * i / PAL_SLOT_COUNT);  // light gray
#endif
			canvas.setPalette(palOffset + i * PAL_SLOT_SIZE + j, hsvToRGB(hsv));
		}
	}
}

void setPalettes() {
	const uint32_t *bgPalette = bg_palettes[bgIndex];
	int bgPalCount = bg_palette_counts[bgIndex];
	int hue = hueValues[pmLevel];
	if (hue == -1) {
		canvas.setPalette(bgPalette, bgPalCount, PAL_BG_OFFSET);
	} else {
		canvas.setPalette2(bgPalette, bgPalCount, PAL_BG_OFFSET, hue, 60, pmLevel < PMLEVEL_COUNT - 1 ? 0 : -40);
	}
	setPaletteForBlend(bgPalette, PAL_BG_COUNT, PAL_BG_OFFSET, hue);

	canvas.setPalette(2, (uint16_t)scoreColors[pmLevel]); // Score
	canvas.setPalette(1, (uint16_t)(pmLevel >= 4 ? TFT_WHITE : TFT_BLACK));
}

void setSpritePalettes() {
	int i = kid.isGirl ? 1 : 0;
	canvas.setPalette(sprite_palettes[i], sprite_palette_counts[i], PAL_SPRITE_OFFSET);
	setPaletteForBlend(sprite_palettes[i], sprite_palette_counts[i], PAL_SPRITE_OFFSET);
}

void drawSprite(int cx, int cy, bool mirror, int index, int frame) {
	const SpriteHeader* header = &sprite_headers[index];
	int w = header->width;
	int h = header->height;
	int dx = header->pivotX ? header->pivotX : w / 2;
	int dy = header->pivotY ? header->pivotY : h;
	int offset = IS_RLE ? sprite_frame_offsets[index][frame] : w * h * frame;
	const uint8_t *image = sprite_images[index] + offset;
	canvas.drawBitmap(cx - dx, cy - dy, w, h, image, PAL_SPRITE_OFFSET, true, mirror ^ SPRITE_MIRROR);

	// draw tears
	const EffectHeader* eHeader = &effect_headers[0];
	int tw = eHeader->width;
	int th = eHeader->height;
	for (int i = 0; i < MAX_TEARS; i++) {
		Tear& tear = kid.tears[i];
		if (tear.dx != 0) {
			canvas.drawBitmap(cx + tear.dx - tw / 2, cy - dy + tear.dy, tw, th, tears, PAL_TEAR, true);
		}
	}
}

 void createParticles(int maxCount) {
	for (int i = 0; i < maxCount; i++) {
		particles[i] = new Particle();
	}
}

void updateParticles() {
	int count = particleCounts[pmLevel];
	for (int i = 0; i < count; i++) {
		particles[i]->update();
	}
}

void drawParticles() {
	int count = particleCounts[pmLevel];
	for (int i = 0; i < count; i++) {
		Particle *p = particles[i];
		if (p->isShow) {
			canvas.blendBitmap(p->getX(), p->getY(), PARTICLE_SIZE, PARTICLE_SIZE, Particle::getImage(), p->dimmer
				, PAL_FIRE_OFFSET, PAL_SLOT_SIZE, PAL_SLOT_COUNT, PAL_PARTICLE);
		}
	}
}

void drawSensorIcon(int x, int y) {
	int index = 10;
	int w = font_headers[0].width;
	int h = font_headers[0].height;
	const uint8_t *bitmap = font_36 + ((IS_RLE ? font_frame_offsets[0][index] : w * index));
	canvas.drawBitmap(x - w, y, w, h, bitmap, 0, true);
}

void changeAppMode() {
	if (appMode == APPMODE_ANIM) {
		canvas.endMT();
	}
	if (++appMode >= APPMODE_COUNT) {
		appMode = APPMODE_ANIM;
	}
	if (appMode == APPMODE_ANIM) {
		canvas.beginMT();
	}
	delay(100); // wait for DMA
	M5.Lcd.fillScreen(TFT_BLACK); // fix INFO->ANIM trouble
}

void pmLevelchanged() {
	pmLevel = (pmStep == -1) ? pmSensor.pmLevel : pmStep;
	setPalettes();
	pmLevelChangedTick = fps.getTick();
}

//
// setup()
//
void setup() {
	pinMode(TFT_RST, INPUT_PULLDOWN);
	delay(1);
	canvas.isIPS = digitalRead(TFT_RST);
	Serial.print("LCD: "); Serial.println(canvas.isIPS ? "IPS " : "TN");

	M5.begin();
	Wire.begin();

	if (digitalRead(BUTTON_A_PIN) == 0) {
		Serial.println("Will Load menu binary");
		updateFromFS(SD);
		ESP.restart();
	}

	M5.Lcd.fillScreen(TFT_BLACK);
	lcdWidth = M5.Lcd.width();
	lcdHeight = M5.Lcd.height();

	prefsBegin();
	bool isMute = prefs.getBool(PKEY_MUTE, false);
	kid.isGirl = prefs.getBool(PKEY_GIRL, false);

	if (M5.BtnC.isPressed()) {
		isMute = !isMute;
		prefsPutBool(PKEY_MUTE, isMute);
		M5.Lcd.setTextColor(isMute ? TFT_YELLOW : TFT_GREEN);
		M5.Lcd.drawCentreString(isMute ? "Mute Sound" : "Play Sound", lcdWidth / 2, lcdHeight / 2, 4);
		while (M5.BtnC.isPressed()) {
			M5.BtnC.read();
		}
	}

	if (pmSensor.init()) {
		Serial.println("PSMA003/SHT20 found");
		pmStep = -1;
	} else {
		Serial.println("PSMA003/SHT20 not found");
	}

	canvas.setColorDepth(8);
	Serial.print("initialize DMA ...");
	canvas.createFrameBuffer(lcdWidth, lcdHeight);
	Serial.println(" done.");

	Serial.println("setPalettes");
	setPalettes();
	setSpritePalettes();

	kid.init(lcdWidth / 2, lcdHeight - 16, lcdWidth);
	canvas.setPalette(PAL_TEAR + 1, (uint16_t)TFT_CYAN); // TODO

	Particle::init(lcdWidth, lcdHeight);
	createParticles(MAX_PARTICLES);
	canvas.setPalette(PAL_PARTICLE, (uint16_t)TFT_PARTICLE);

	fireEffect.init(FIRE_WIDTH, FIRE_HEIGHT);
	canvas.setPalette(firePalettes, FIRE_PALETTE_COUNT, PAL_FIRE_OFFSET);
	setPaletteForBlend(firePalettes, FIRE_PALETTE_COUNT, PAL_FIRE_OFFSET);

	Serial.println("setup audio");
	audio.setVolume(4);
	audio.setMute(isMute);
	audio.setSampleRate(SAMPLE_RATE);
	audio.setWaveData(waveDataArray, waveDataSizeArray);

	Serial.println("drawBitmap");
	canvas.drawBitmap(bg_images[bgIndex], PAL_BG_OFFSET);

	Serial.println("flush");
	canvas.flush();
	Serial.println("setup done");
//	delay(5000);
}

//
// loop()
//
void loop() {
	M5.update();

	bool redraw = false;

	if (M5.BtnA.wasPressed()) {
		if (appMode == APPMODE_INFO) {
			changeAppMode();
			pmStep = -1;
			pmLevelchanged();
			redraw = true;
		} else {
			kid.toggleSprite();
			prefsPutBool(PKEY_GIRL, kid.isGirl);
			setSpritePalettes();
			pmLevelChangedTick = fps.getTick();
		}
//		if (++bgIndex >= BG_COUNT) {
//			bgIndex = 0;
//		}
//		setPalettes();
	}
	if (M5.BtnB.wasPressed()) {
		if (appMode == APPMODE_INFO && pmSensor.isAvailable) {
			changeAppMode();
			pmStep = -1;
		} else {
			if (++pmStep >= PMLEVEL_COUNT) {
				pmStep = pmSensor.isAvailable ? -1 : 0;
				fireEffect.clear();
			}
		}
		pmLevelchanged();
		redraw = true;
	}
	if (pmSensor.isAvailable && pmStep >= 0) {
		if (fps.getTick() - pmLevelChangedTick >= RETURN_TO_SENSING) {
			pmStep = -1;
			fireEffect.clear();
			pmLevelchanged();
			redraw = true;
		}
	}

	if (M5.BtnC.wasPressed()) {
		changeAppMode();
		if (appMode == APPMODE_INFO && pmSensor.isAvailable) {
			pmStep = -1;
			pmLevelchanged();
		}
		redraw = true;
	}

	if (pmSensor.isAvailable) {
		bool isSHT20 = appMode == APPMODE_INFO;
		if (pmSensor.update(isSHT20)) { // reading SHT20 is very slow
			sensorTick = millis();
			redraw = true;
			pmSensor.debugPrintValues(isSHT20);
			if (pmStep == -1) {
				if (pmLevel != pmSensor.pmLevel) {
					pmLevel = pmSensor.pmLevel;
					setPalettes();
				}
			}
		}
	}

	int n = fps.getFPS();

	if (fps.updateFPS(APP_FPS)) {
		if (appMode == APPMODE_ANIM) {
			Serial.printf("%d FPS\r\n", n);
		} else if (!pmSensor.isAvailable) {
			redraw = true;
		}
	}

	if (appMode != APPMODE_ANIM) {
		if (appMode == APPMODE_INFO && redraw) {
			Serial.println("draw sensor values");
			pmSensor.drawValues(lcdWidth, lcdHeight, pmLevel);
		}
		delay(100);
		return;
	}

	updateParticles();
	if (bgIndex == 0 && pmLevel > 0) {
		fireEffect.update((pmLevel == 1) ? 1 : pmLevel * 2, FIRE_MAX_POWER);
	}

	canvas.drawBitmap(bg_images[bgIndex], PAL_BG_OFFSET);
	if (bgIndex == 0 && pmLevel > 0) {
		canvas.drawBitmap(FIRE_X, FIRE_Y, FIRE_WIDTH, FIRE_HEIGHT, fireEffect.getImage(), PAL_FIRE_OFFSET);
	}

	kid.setSickLevel(pmLevel);
	int spriteIndex = kid.getSpriteIndex();
	drawSprite(kid.x, kid.y, kid.mirror, spriteIndex, kid.frame);

	drawParticles();

	int num = !pmSensor.isAvailable ? n : pmStep == -1 ? pmSensor.aqiValue : aqiValues[pmLevel];
	canvas.drawNumber(SCORE_X, SCORE_Y, num, 3, font_36, IS_RLE ? font_frame_offsets[0] : NULL,
		font_headers[0].width, font_headers[0].height, font_headers[0].spacing);
	if (pmSensor.isAvailable && pmStep == -1) {
		if (fps.getTick() - sensorTick < 500) { // flash sensor icon
			drawSensorIcon(SCORE_X, SCORE_Y);
		}
	}
	canvas.flush();

	if (kid.update(APP_FPS, sprite_headers[spriteIndex].count)) {
		if (kid.mode == KID_WALK) {
			if (kid.frame == 0) {
				audio.play(kid.isSick ? SND_FOOTSTEP3 : SND_FOOTSTEP1);
			} else if (kid.frame == 4) {
				audio.play(kid.isSick ? SND_FOOTSTEP4 : SND_FOOTSTEP2);
			}
		}
	}
	if (kid.isTearDropped) {
		audio.play(SND_WATERDROP);
	}
}
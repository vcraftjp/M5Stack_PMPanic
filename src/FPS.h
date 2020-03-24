//
// FPS.h
//
#pragma once

#include <arduino.h>

class FPS {
public:
	FPS(int _period = 1000) {
		period = _period;
		tick = millis();
		elapse = 0;
		fps = 0;
		count = 0;
	}

	int getFPS() {
		return fps;
	}

	unsigned long getTick() {
		return tick;
	}

	int updateFPS(int appFps = 0) {
		count++;
		unsigned long t = millis();
		int e = (int)(t - tick);
		tick = t;
		elapse += e;
		if (appFps > 0) {
			int w = (1000 / appFps) - e;
			if (w > 0) {
				delay(w);
			}
		}
		if (elapse >= period) {
			fps = count;
			elapse = 0;
			count = 0;
			return fps;
		}
		return 0;
	}

private:
	unsigned long tick;
	int elapse;
	int period;
	int count;
	int fps;
};

//
// PMSensor.h
//
#pragma once

#include <M5Stack.h>
#include "DFRobot_SHT20.h"

#define PMLEVEL_COUNT 6

#define BUFFER_SIZE 16
#define PMCTYPE_COUNT 3 // PM concentration unit (n) μg/m3
#define PMDIAMETER_COUNT 6 // number of particles with diameter beyond (n) μm in 0.1L of air

extern const int16_t aqiValues[PMLEVEL_COUNT];

//
// PMSensor class
//
class PMSensor {
public:
	PMSensor() : isAvailable(false), isReady(false), temperature(0.0f), humidity(0.0f) {}

	bool init();
	bool update(bool isSHT20 = false);
	void drawValues(int16_t width, int16_t height, int _pmLevel = -1);
	void debugPrintValues(bool isSHT20 = false);

	bool isAvailable;
	bool isReady;
	float temperature;
	float humidity;
	int pmLevel;
	int aqiValue;

private:
	uint16_t pmconc[PMCTYPE_COUNT * 2]; // standard particle, under atmospheric environment
	uint16_t pmdiam[PMDIAMETER_COUNT];

	DFRobot_SHT20 sht20;
	uint16_t readBuffer[BUFFER_SIZE];
	int readIndex;

	void setPMParam();
	float validateI2CValue(float value) {
		return (value == ERROR_I2C_TIMEOUT || value == ERROR_BAD_CRC) ? 0.0f : value;
	}

	void calcAQIValue(float pmc);

	char str[8]; // number to string buffer
	char* intToStr(int n);
	char* floatToStr(float n);
};
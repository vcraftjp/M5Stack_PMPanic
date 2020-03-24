//
// PMSensor.cpp
//

#include "PMSensor.h"

#define HEADER_HEIGHT 64

#define FONT2 2
#define FONT4 4
#define FONT6 6

static const char* pmcLabels[] = { "PM1.0", "PM2.5", "PM10" };
static const char* pmdLabels[] = { "0.3", "0.5", "1.0", "2.0", "5.0", "10" };
static uint16_t aqiColors[PMLEVEL_COUNT] = { TFT_GREEN, TFT_YELLOW, TFT_ORANGE, TFT_RED, TFT_PURPLE, TFT_MAROON };
static uint16_t bgColors[PMLEVEL_COUNT] = { 0x02A0, 0x52A0, 0x51C0, 0x5000, 0x4008, 0x4000 };

const int16_t aqiValues[PMLEVEL_COUNT] = { 0, 50, 100, 150, 200, 300 };
const float pmConcentrations[PMLEVEL_COUNT + 1] = { 0.0f, 15.5f, 40.5f, 65.5f, 150.5f, 250.5f, 500.5f };

void PMSensor::calcAQIValue(float pmc) {
	int i = 0;
	for (; i < PMLEVEL_COUNT - 1; i++) {
		if (pmc < pmConcentrations[i + 1]) break;
	}
	pmLevel = i;
	float aqiMax = aqiValues[i + 1];
	float aqiMin = aqiValues[i] + 1;
	float pmMax = pmConcentrations[i + 1];
	float pmMin = pmConcentrations[i];
	aqiValue = (int)((aqiMax - aqiMin) / (pmMax - pmMin) * (pmc - pmMin) + aqiMin);
}

bool PMSensor::init() {
//	Wire.begin();
	Wire.beginTransmission(SLAVE_ADDRESS);
    if (Wire.endTransmission() != 0) return false;

	// PMSA003 serial setup
	Serial2.begin(9600, SERIAL_8N1, 16, 17);
	pinMode(10, OUTPUT);
	digitalWrite(10, 1);

	sht20.initSHT20();
	delay(100);
	sht20.checkSHT20();

	isAvailable = true;
	readIndex = 0;
	return true;
}

bool PMSensor::update(bool isSHT20) {
	if (!isAvailable) return false;
	isReady = false;
	uint16_t high = 0;
	while (Serial2.available()) {
		uint8_t b = Serial2.read();
		if ((readIndex & 1) == 0) {
			high = b;
		} else {
			readBuffer[readIndex >> 1] = high << 8 | b;
		}
		if (++readIndex >= BUFFER_SIZE * 2) {
			readIndex = 0;
			setPMParam();
			calcAQIValue(pmconc[1]); // PM2.5 standard
			if (isSHT20) {
				humidity = validateI2CValue(sht20.readHumidity());
				temperature = validateI2CValue(sht20.readTemperature());
			}
			isReady = true;
		}
	}
	return isReady;
}

void PMSensor::setPMParam() {
	uint16_t *p = &readBuffer[2];
	for (int i = 0; i < PMCTYPE_COUNT * 2; i++) {
		pmconc[i] = *p++;
	}
	for (int i = 0; i < PMDIAMETER_COUNT; i++) {
		pmdiam[i] = *p++;
	}
}

void PMSensor::drawValues(int16_t width, int16_t height, int _pmLevel) {
	if (_pmLevel == -1) _pmLevel = pmLevel;

	M5.Lcd.fillRect(0, 0, width, HEADER_HEIGHT, aqiColors[_pmLevel]);

	int font2H = M5.Lcd.fontHeight(FONT2);
	int font4H = M5.Lcd.fontHeight(FONT4);
	int font6H = M5.Lcd.fontHeight(FONT6);
	M5.Lcd.setTextColor(_pmLevel < 4 ? TFT_BLACK : TFT_WHITE);

	M5.Lcd.drawCentreString(intToStr(aqiValue), width / 2,  (HEADER_HEIGHT - font6H) / 2 + 4, FONT6);
	M5.Lcd.drawString("AQI", width / 2 + 48,  HEADER_HEIGHT - font4H - 8, FONT4);

	M5.Lcd.fillRect(0, HEADER_HEIGHT, width, height - HEADER_HEIGHT, bgColors[_pmLevel]);

	M5.Lcd.setTextColor(TFT_WHITE);
	for (int i = 0; i < PMCTYPE_COUNT; i++) {
		int x = width / 2 + (i - 1) * 80;
		int y = HEADER_HEIGHT + 8;
		M5.Lcd.drawCentreString(pmcLabels[i], x, y, FONT4);
		M5.Lcd.drawCentreString(intToStr(pmconc[i]), x, y + font4H, FONT4);
	}
	M5.Lcd.setTextColor(0xD69A); // 208,208,208
	for (int i = 0; i < PMDIAMETER_COUNT; i++) {
		int space =  ((width - 10 * 2) / PMDIAMETER_COUNT);
		int x = space * i + 10 + space / 2;
		int y = HEADER_HEIGHT + 68;
		M5.Lcd.drawCentreString(pmdLabels[i], x, y, FONT2);
		M5.Lcd.drawCentreString(intToStr(pmdiam[i]), x, y + font2H, FONT4);
	}

	int x = width / 2 - 40;
	int y = height - font6H;
    M5.Lcd.setTextColor(TFT_YELLOW);
    M5.Lcd.drawRightString(floatToStr(temperature), x, y, FONT6);
    M5.Lcd.drawString("`c", x + 8, y + 16, FONT4);
	x = width - 60;
    M5.Lcd.setTextColor(TFT_CYAN);
    M5.Lcd.drawRightString(floatToStr(humidity), x, y, FONT6);
    M5.Lcd.drawString("%", x + 8, y + 16, FONT4);
}

void PMSensor::debugPrintValues(bool isSHT20) {
	Serial.print("PM: ");
	for (int i = 0; i < PMCTYPE_COUNT * 2; i++) {
		Serial.printf("%d", pmconc[i]);
		Serial.print((i % 3) < 2 ? "/" : " ");
	}
	for (int i = 0; i < PMDIAMETER_COUNT; i++) {
		Serial.printf("%d", pmdiam[i]);
		if (i < PMDIAMETER_COUNT - 1 ) {
			Serial.print(",");
		}
	}
	if (isSHT20) {
		Serial.printf("\r\nTemp: %.1f Hum: %.1f", temperature, humidity);
	}
	Serial.println("");
}

char* PMSensor::intToStr(int n) {
	snprintf(str, sizeof(str) - 1, "%d", n);
	return str;
}

char* PMSensor::floatToStr(float n) {
	snprintf(str, sizeof(str) - 1, "%.1f", n);
	return str;
}

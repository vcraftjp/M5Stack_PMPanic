//
// mydefs.h
//
#pragma once

#ifndef _countof
#define _countof(a) (sizeof(a) / sizeof(a[0]))
#endif

#ifndef max
#define max(a, b) ((a >= b) ? a : b)
#endif
#ifndef min
#define min(a, b) ((a <= b) ? a : b)
#endif

#define _print(v) { M5.Lcd.print(v); Serial.print(v); }
#define _println(v) { M5.Lcd.println(v); Serial.println(v); }
#define _printf(...) { M5.Lcd.printf(__VA_ARGS__); Serial.printf(__VA_ARGS__); }

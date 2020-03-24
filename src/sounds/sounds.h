#define SAMPLE_RATE 8000

#include "footstep1.h"
#include "footstep2.h"
#include "footstep3.h"
#include "footstep4.h"
#include "waterdrop.h"

#define SND_FOOTSTEP1 0
#define SND_FOOTSTEP2 1
#define SND_FOOTSTEP3 2
#define SND_FOOTSTEP4 3
#define SND_WATERDROP 4

#define SOUND_COUNT 5

const uint8_t *waveDataArray[] = {
	footstep1,
	footstep2,
	footstep3,
	footstep4,
	waterdrop,
};

const uint16_t waveDataSizeArray[] = {
	sizeof(footstep1),
	sizeof(footstep2),
	sizeof(footstep3),
	sizeof(footstep4),
	sizeof(waterdrop),
};

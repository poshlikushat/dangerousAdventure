#pragma once

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define STRNCPY(dest, src, n) \
	strncpy(dest, src, n);    \
	dest[n - 1] = '\0'

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define FPS 60.0
#define LOGIC_RATE (FPS / 1000)

#define MAX_FILENAME_LENGTH 256

#define NUM_ATLAS_BUCKETS 64

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16

#define TILE_SIZE 64

#define MAX_TILES 64

#define MAP_WIDTH 19
#define MAP_HEIGHT 10

#define TILE_HOLE 0
#define TILE_GROUND 1

enum
{
	FACING_LEFT,
	FACING_RIGHT
};

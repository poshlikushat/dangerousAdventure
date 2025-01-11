#pragma once

typedef struct AtlasImage AtlasImage;
typedef struct Texture Texture;
typedef struct Entity Entity;

struct AtlasImage
{
	char filename[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	SDL_Rect rect;
	int rotated;
	AtlasImage *next;
};

struct Texture
{
	char name[MAX_FILENAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct
{
	int data[MAP_WIDTH][MAP_HEIGHT];
} Map;

struct Entity
{
	int x;
	int y;
	int facing;
	AtlasImage *texture;
	Entity *next;
};

typedef struct
{
	SDL_Point renderOffset;
	SDL_Point camera;
	Entity entityHead, *entityTail;
	Map map;
} Dungeon;

typedef struct
{
	struct
	{
		void (*logic)(void);
		void (*draw)(void);
	} delegate;
	SDL_Renderer *renderer;
	SDL_Window *window;
	int keyboard[MAX_KEYBOARD_KEYS];
	double deltaTime;
	struct
	{
		int fps;
	} dev;
} App;
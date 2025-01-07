#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "draw.h"

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

extern App app;

typedef struct {
	int x;
	int y;
	SDL_Texture *texture;
} Entity;

extern Entity player;
#pragma once
#include <SDL.h>

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

extern App app;
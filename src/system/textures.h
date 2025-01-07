#pragma once

#include "../common.h"

SDL_Texture *loadTexture(char *filename);
SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface);
void initTextures(void);
#pragma once

#include "../common.h"

void blitAtlasImage(AtlasImage *atlasImage, int x, int y, int center, SDL_RendererFlip flip);
void blit(SDL_Texture *texture, int x, int y, int center);
void presentScene(void);
void prepareScene(void);

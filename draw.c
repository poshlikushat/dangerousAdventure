#include <SDL.h>
#include "structs.h"
#include "draw.h"

void prepareScene(void) {
	SDL_SetRenderDrawColor(app.renderer, 250, 250, 250, 255);
	SDL_RenderClear(app.renderer);
}

void presentScene(void) {
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename) {
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
}

void blit(SDL_Texture *texture, int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, (void*)0, (void*)0, &dest.w, &dest.h);

	dest.w *= 2;
	dest.h *= 2;

	SDL_RenderCopy(app.renderer, texture, (void*)0, &dest);
}


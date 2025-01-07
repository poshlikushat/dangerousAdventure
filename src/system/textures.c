#include <SDL_image.h>

#include "../common.h"

#include "textures.h"

extern App app;

static Texture textureHead;
static Texture *textureTail;

void initTextures(void)
{
	memset(&textureHead, 0, sizeof(Texture));

	textureTail = &textureHead;
}

static SDL_Texture *getTexture(char *name)
{
	Texture *t;

	for (t = textureHead.next; t != NULL; t = t->next)
	{
		if (strcmp(t->name, name) == 0)
		{
			return t->texture;
		}
	}

	return NULL;
}

static void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
	Texture *texture;

	texture = malloc(sizeof(Texture));
	memset(texture, 0, sizeof(Texture));
	textureTail->next = texture;
	textureTail = texture;

	STRNCPY(texture->name, name, MAX_FILENAME_LENGTH);
	texture->texture = sdlTexture;
}

SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface)
{
	SDL_Texture *texture;

	texture = SDL_CreateTextureFromSurface(app.renderer, surface);

	if (destroySurface)
	{
		SDL_FreeSurface(surface);
	}

	return texture;
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	texture = getTexture(filename);

	if (texture == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s ...", filename);
		texture = IMG_LoadTexture(app.renderer, filename);
		addTextureToCache(filename, texture);
	}

	return texture;
}

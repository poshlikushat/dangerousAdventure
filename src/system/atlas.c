#include <SDL_image.h>

#include "../common.h"

#include "../json/cJSON.h"
#include "../system/util.h"
#include "atlas.h"

extern App app;

static void loadAtlasData(void);

static AtlasImage atlases[NUM_ATLAS_BUCKETS];
static SDL_Texture *atlasTexture;

void initAtlas(void)
{
	memset(&atlases, 0, sizeof(AtlasImage) * NUM_ATLAS_BUCKETS);

	atlasTexture = IMG_LoadTexture(app.renderer, "../../gfx/atlas.png");

	loadAtlasData();
}

AtlasImage *getAtlasImage(char *filename, int required)
{
	AtlasImage *a;
	unsigned long i;

	i = hashcode(filename) % NUM_ATLAS_BUCKETS;

	for (a = atlases[i].next; a != NULL; a = a->next)
	{
		if (strcmp(a->filename, filename) == 0)
		{
			return a;
		}
	}

	if (required)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "No such atlas image '%s'", filename);
		exit(1);
	}

	return NULL;
}

static void loadAtlasData(void)
{
	AtlasImage *atlasImage, *a;
	int x, y, w, h, rotated;
	cJSON *root, *node;
	char *text, *filename;
	unsigned long i;

	text = readFile("../../data/atlas.json");

	if (text == (void*)0) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Failed to load atlas.json: %s", cJSON_GetErrorPtr());
		free(text);
		exit(1);
	}

	root = cJSON_Parse(text);

	if (root == NULL)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_CRITICAL, "Failed to parse atlas.json: %s", cJSON_GetErrorPtr());
		free(text);
		exit(1);
	}

	for (node = root->child; node != NULL; node = node->next)
	{
		filename = cJSON_GetObjectItem(node, "filename")->valuestring;
		x = cJSON_GetObjectItem(node, "x")->valueint;
		y = cJSON_GetObjectItem(node, "y")->valueint;
		w = cJSON_GetObjectItem(node, "w")->valueint;
		h = cJSON_GetObjectItem(node, "h")->valueint;
		rotated = cJSON_GetObjectItem(node, "rotated")->valueint;

		i = hashcode(filename) % NUM_ATLAS_BUCKETS;

		a = &atlases[i];

		/* horrible bit to look for the tail */
		while (a->next)
		{
			SDL_Log("Traversing list: current filename = %s", a->filename);
			a = a->next;
		}

		atlasImage = malloc(sizeof(AtlasImage));
		memset(atlasImage, 0, sizeof(AtlasImage));
		a->next = atlasImage;

		STRNCPY(atlasImage->filename, filename, MAX_FILENAME_LENGTH);
		atlasImage->rect.x = x;
		atlasImage->rect.y = y;
		atlasImage->rect.w = w;
		atlasImage->rect.h = h;
		atlasImage->rotated = rotated;

		atlasImage->texture = atlasTexture;
	}

	cJSON_Delete(root);

	free(text);
}

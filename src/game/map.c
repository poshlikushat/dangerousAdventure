#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "map.h"

extern Dungeon dungeon;

static void loadTiles(void);
static void drawMapTiles(void);

static AtlasImage *tiles[MAX_TILES];

void initMap(void)
{
	int x, y;

	loadTiles();

	for (x = 0; x < MAP_WIDTH; x++)
	{
		for (y = 0; y < MAP_HEIGHT; y++)
		{
			dungeon.map.data[x][y] = TILE_GROUND;
		}
	}
}

void drawMap(void)
{
	drawMapTiles();
}

static void drawMapTiles(void)
{
	int x, y, n;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			n = dungeon.map.data[x][y];

			if (n > TILE_HOLE)
			{
				blitAtlasImage(tiles[n], (x * TILE_SIZE) + dungeon.renderOffset.x, (y * TILE_SIZE) + dungeon.renderOffset.y, 0, SDL_FLIP_NONE);
			}
		}
	}
}

static void loadTiles(void)
{
	int i;
	char filename[MAX_FILENAME_LENGTH];

	for (i = 1; i <= MAX_TILES; i++)
	{
		sprintf(filename, "gfx/tiles/%d.png", i);

		tiles[i] = getAtlasImage(filename, 0);
	}
}

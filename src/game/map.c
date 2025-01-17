#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/util.h"
#include "map.h"

extern Dungeon dungeon;

static void loadTiles(void);
static void drawMapTiles(void);
static void loadMap(void);
static void decorateMap(void);

static AtlasImage *tiles[MAX_TILES];

void initMap(void)
{
	int x, y;

	loadTiles();

	loadMap();

	decorateMap();

}

void drawMap(void)
{
	drawMapTiles();
}

static void drawMapTiles(void)
{
	int x, y, mx, my, n;

	for (y = 0; y < MAP_RENDER_HEIGHT; y++)
	{
		for (x = 0; x < MAP_RENDER_WIDTH; x++)
		{
			mx = dungeon.camera.x + x;
			my = dungeon.camera.y + y;

			n = dungeon.map.data[mx][my];

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

static void loadMap() {
	int x, y;
	char *data, *p;

	data = readFile("../../data/map.data");

	if (data == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error: Failed to open file ../../data/map.data: %s\n", SDL_GetError());
		exit(1);
	}

	p = data;
	
	for(y = 0; y < MAP_HEIGHT; y++) {
		for (x = 0; x < MAP_WIDTH; x++) {
			dungeon.map.data[x][y] = atoi(p);

			do {p++;} while (*p != ' ');
		}
	}

	free(data);
}

static void decorateMap() {
	int x, y;

	srand(144893);

	for (x = 0; x < MAP_WIDTH; x++) {
		for (y = 0; y < MAP_HEIGHT; y++) {
			if (dungeon.map.data[x][y] == TILE_GROUND && rand() % 5 == 0)
			{
				dungeon.map.data[x][y] += (1 + rand() % 4);
			}

			if (dungeon.map.data[x][y] == TILE_WALL)
			{
				dungeon.map.data[x][y] += rand() % 6;
			}
		}
	}
}

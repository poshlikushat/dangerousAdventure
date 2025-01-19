#include "../common.h"

#include "../system/atlas.h"
#include "../system/draw.h"
#include "../system/util.h"
#include "fogOfWar.h"

extern Dungeon dungeon;
extern Entity *player;

static VisData visData[MAP_WIDTH][MAP_HEIGHT];
static AtlasImage *fogOfWarRect;

static int hasLOS(int x1, int y1, int x2, int y2);

	void initFogOfWar(void)
{
	fogOfWarRect = getAtlasImage("gfx/misc/fogOfWarRect.png", true);
}

void updateFogOfWar(void) {
	int x, y, mx, my, lightLevel;
	double distance;
	Entity *e;

	for (x = 0; x < MAP_WIDTH; x++) {
		for (y = 0; y < MAP_HEIGHT; y++) {
			visData[x][y].hasSolidEntity = false;
		}
	}

	for (e = dungeon.entityHead.next; e != (void*)0; e = e->next) {
		if (e->solid) {
			visData[e->x][e->y].hasSolidEntity = true;
		}
	}

	for (y = -VIS_DISTANCE; y <= VIS_DISTANCE; y++) {
		for (x = -VIS_DISTANCE; x <= VIS_DISTANCE; x++) {
			mx = player->x + x;
			my = player->y + y;

			if (mx >= 0 && my >= 0 && mx < MAP_WIDTH && my < MAP_HEIGHT && visData[mx][my].lightLevel < 255 && hasLOS(player->x, player->y, mx, my)) {
				distance = getDistance(player->x, player->y, mx, my);

				if (distance <= 1) {
					lightLevel = 255;
				} else {
					lightLevel = 255 - (255 * distance / VIS_DISTANCE);
				}

				visData[mx][my].lightLevel = MAX(lightLevel, visData[mx][my].lightLevel);
			}
		}
	}
}

// Bresenham's line algorithm
static int hasLOS(int x1, int y1, int x2, int y2) {
	int dx, dy, sx, sy, err, e2;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	sx = (x1 < x2) ? 1 : -1;
	sy = (y1 < y2) ? 1 : -1;
	err = dx - dy;

	while (1)
	{
		e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y1 += sy;
		}

		if (x1 == x2 && y1 == y2)
		{
			return 1;
		}

		if (dungeon.map.data[x1][y1] >= TILE_WALL || visData[x1][y1].hasSolidEntity)
		{
			return 0;
		}
	}

	return 0;
}

void drawFogOfWar(void) {
	int x, y, mx, my, alpha;

	for (y = 0; y < MAP_RENDER_HEIGHT; y++)
	{
		for (x = 0; x < MAP_RENDER_WIDTH; x++)
		{
			mx = dungeon.camera.x + x;
			my = dungeon.camera.y + y;

			if (mx >= 0 && my >= 0 && mx < MAP_WIDTH && my < MAP_HEIGHT)
			{
				alpha = 255 - visData[mx][my].lightLevel;

				SDL_SetTextureAlphaMod(fogOfWarRect->texture, alpha);

				blitAtlasImage(fogOfWarRect, (x * TILE_SIZE) + dungeon.renderOffset.x, (y * TILE_SIZE) + dungeon.renderOffset.y, 0, SDL_FLIP_NONE);
			}
		}
	}

	SDL_SetTextureAlphaMod(fogOfWarRect->texture, 255);
}

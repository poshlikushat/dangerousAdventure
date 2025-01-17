#include "../common.h"

#include "../game/entities.h"
#include "../system/atlas.h"
#include "player.h"

extern App app;
extern Dungeon dungeon;
extern Entity *player;

static void movePlayer(int dx, int dy);

static double moveDelay;

void initPlayer(void)
{
	player = spawnEntity();

	player->x = 14;
	player->y = 28;
	player->texture = getAtlasImage("gfx/entities/prisoner.png", 1);
	player->facing = FACING_RIGHT;

	movePlayer(0, 0);

	moveDelay = 0;
}

void doPlayer(void)
{
	moveDelay = MAX(0, moveDelay - app.deltaTime);

	if (moveDelay == 0)
	{
		if (app.keyboard[SDL_SCANCODE_A])
		{
			movePlayer(-1, 0);

			player->facing = FACING_LEFT;
		}

		if (app.keyboard[SDL_SCANCODE_D])
		{
			movePlayer(1, 0);

			player->facing = FACING_RIGHT;
		}

		if (app.keyboard[SDL_SCANCODE_W])
		{
			movePlayer(0, -1);
		}

		if (app.keyboard[SDL_SCANCODE_S])
		{
			movePlayer(0, 1);
		}
	}
}

static void movePlayer(int dx, int dy)
{
	int x, y;

	x = player->x + dx;
	y = player->y + dy;

	x = MAX(0, MIN(x, MAP_WIDTH - 1));
	y = MAX(0, MIN(y, MAP_HEIGHT - 1));

	if (dungeon.map.data[x][y] >= TILE_GROUND && dungeon.map.data[x][y] < TILE_WALL)
	{
		player->x = x;
		player->y = y;

		dungeon.camera.x = x;
		dungeon.camera.x -= (MAP_RENDER_WIDTH / 2);
		dungeon.camera.x = MIN(MAX(dungeon.camera.x, 0), MAP_WIDTH - MAP_RENDER_WIDTH);

		dungeon.camera.y = y;
		dungeon.camera.y -= (MAP_RENDER_HEIGHT / 2);
		dungeon.camera.y = MIN(MAX(dungeon.camera.y, 0), MAP_HEIGHT - MAP_RENDER_HEIGHT);

		moveDelay = 5;
	}
}

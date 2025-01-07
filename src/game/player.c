#include "../common.h"

#include "../game/entities.h"
#include "../system/atlas.h"
#include "player.h"

extern App app;
extern Entity *player;

static void movePlayer(int dx, int dy);

static double moveDelay;

void initPlayer(void)
{
	player = spawnEntity();

	player->x = 5;
	player->y = 5;
	player->texture = getAtlasImage("gfx/entities/prisoner.png", 1);

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

	player->x = x;
	player->y = y;

	moveDelay = 5;
}

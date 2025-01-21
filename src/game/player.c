#include "../common.h"

#include "../game/entities.h"
#include "../game/fogOfWar.h"
#include "../system/atlas.h"
#include "player.h"

extern App app;
extern Dungeon dungeon;
extern Entity *player;

static void movePlayer(int dx, int dy);

static double moveDelay;
static void attackEntity(void);

	void initPlayer(void)
{
	player = spawnEntity();

	player->x = 14;
	player->y = 28;
	player->texture = getAtlasImage("gfx/entities/prisoner.png", 1);
	player->facing = FACING_RIGHT;
	player->health = 1;

	movePlayer(0, 0);

	moveDelay = 0;
}

//add ability to attack via arrows (because facing with space isn't working)
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

		if (app.keyboard[SDL_SCANCODE_UP])
		{
			attackEntity();
		}

		if (app.keyboard[SDL_SCANCODE_DOWN])
		{
			attackEntity();
		}

		if (app.keyboard[SDL_SCANCODE_LEFT])
		{
			attackEntity();
		}
		
		if (app.keyboard[SDL_SCANCODE_RIGHT])
		{
			attackEntity();
		}
	}
}

static void movePlayer(int dx, int dy)
{
	int x, y;
	Entity *e;

	x = player->x + dx;
	y = player->y + dy;

	x = MAX(0, MIN(x, MAP_WIDTH - 1));
	y = MAX(0, MIN(y, MAP_HEIGHT - 1));

	if (dungeon.map.data[x][y] >= TILE_GROUND && dungeon.map.data[x][y] < TILE_WALL)
	{
		e = getEntityAt(x, y);

		if (e == NULL || e->solid == SOLID_NON_SOLID || e == player)
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

		if (e != NULL && e->touch != NULL)
		{
			e->touch(e, player);
		}

		updateFogOfWar();
	}
}

static void attackEntity(void) {
	int targetX, targetY;

	Entity *target;

	targetX = player->x;
	targetY = player->y;

	switch (player->facing)
	{
	case FACING_LEFT:
		targetX--;
		break;
	case FACING_RIGHT:
		targetX++;
		break;
	case FACING_UP:
		targetY++;
		break;
	case FACING_DOWN:
		targetY--;
		break;
	default:
		return;
	}


	if (targetX < 0 || targetX >= MAP_WIDTH || targetY < 0 || targetY >= MAP_HEIGHT) {
		return;
	}

	target = getEntityAt(targetX, targetY);

	if (target != (void*)0 && target != player) {
		if(target->health > 0) {
			target->health -= 1;
		}

		moveDelay = 15;

		if (target->health <= 0) {
			if (target->alive != ALIVE_DEAD)
			{
				target->alive = ALIVE_DEAD;
				target->solid = SOLID_NON_SOLID;
			}

			else {
				removeEntityFromDungeon(target);
			}
		}
	}
}
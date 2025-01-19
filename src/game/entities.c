#include "../common.h"

#include "../system/draw.h"
#include "entities.h"

extern Dungeon dungeon;

void initEntities(void)
{
	dungeon.entityTail = &dungeon.entityHead;
}

Entity *spawnEntity(void)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	dungeon.entityTail->next = e;
	dungeon.entityTail = e;

	e->facing = FACING_LEFT;

	return e;
}

void doEntities(void)
{
	Entity *e, *prev;

	prev = &dungeon.entityHead;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->alive == ALIVE_DEAD)
		{
			if (e == dungeon.entityTail)
			{
				dungeon.entityTail = prev;
			}

			if (e->data != NULL)
			{
				free(e->data);
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}
}

void drawEntities(void)
{
	Entity *e;
	int x, y;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->alive != ALIVE_DEAD)
		{
			x = e->x - dungeon.camera.x;
			y = e->y - dungeon.camera.y;

			if (x >= 0 && y >= 0 && x < MAP_RENDER_WIDTH && y < MAP_RENDER_HEIGHT)
			{
				x = (x * TILE_SIZE) + (TILE_SIZE / 2);
				y = (y * TILE_SIZE) + (TILE_SIZE / 2);

				x += dungeon.renderOffset.x;
				y += dungeon.renderOffset.y;

				blitAtlasImage(e->texture, x, y, 1, e->facing == FACING_LEFT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
			}
		}
	}
}

Entity *getEntityAt(int x, int y)
{
	Entity *e;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e->x == x && e->y == y)
		{
			return e;
		}
	}

	return NULL;
}

void addEntityToDungeon(Entity *e)
{
	e->next = NULL;

	dungeon.entityTail->next = e;
	dungeon.entityTail = e;
}

void removeEntityFromDungeon(Entity *remove)
{
	Entity *e, *prev;

	prev = &dungeon.entityHead;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		if (e == remove)
		{
			if (e == dungeon.entityTail)
			{
				dungeon.entityTail = prev;
			}

			prev->next = e->next;

			remove->next = NULL;
		}

		prev = e;
	}
}
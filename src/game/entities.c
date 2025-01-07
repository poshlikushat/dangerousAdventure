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

void drawEntities(void)
{
	Entity *e;
	int x, y;

	for (e = dungeon.entityHead.next; e != NULL; e = e->next)
	{
		x = (e->x * TILE_SIZE) + (TILE_SIZE / 2);
		y = (e->y * TILE_SIZE) + (TILE_SIZE / 2);

		x += dungeon.renderOffset.x;
		y += dungeon.renderOffset.y;

		blitAtlasImage(e->texture, x, y, 1, e->facing == FACING_LEFT ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
	}
}

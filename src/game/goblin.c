#include "../common.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../system/util.h"
#include "../game/entities.h"
#include "goblin.h"

Entity *goblins[MAX_GOBLINS];

void initGoblin(void)
{
	int goblinX[] = {27, 9, 5, 18, 36};
	int goblinY[] = {0, 1, 28, 29, 29};

	for (int i = 0; i < MAX_GOBLINS; i++)
	{
		goblins[i] = spawnEntity();

		goblins[i]->x = goblinX[i];
		goblins[i]->y = goblinY[i];

		goblins[i]->texture = getAtlasImage("gfx/entities/goblin.png", 1);
		goblins[i]->solid = SOLID_SOLID;
		goblins[i]->alive = ALIVE_ALIVE;
		goblins[i]->facing = FACING_RIGHT;
		goblins[i]->health = 1;
	}
}
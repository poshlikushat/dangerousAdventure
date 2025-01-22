#include "../common.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../system/util.h"
#include "../game/entities.h"
#include "monsters.h"

Entity *goblins[MAX_GOBLINS];
Entity *bats[MAX_BATS];

void initGoblins(void)
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

void initBats(void) {
	int batsX[] = {10, 28, 30, 0, 17, 19, 17, 14};
	int batsY[] = {29, 15, 14, 9, 9, 9, 1, 1};

	for (int i = 0; i < MAX_BATS; i++) {
		bats[i] = spawnEntity();

		bats[i]->x = batsX[i];
		bats[i]->y = batsY[i];

		bats[i]->texture = getAtlasImage("gfx/entities/vampireBat.png", 1);
		bats[i]->solid = SOLID_NON_SOLID;
		bats[i]->alive = ALIVE_ALIVE;
		bats[i]->health = 1;
	}

}
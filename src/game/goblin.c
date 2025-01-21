#include "../common.h"
#include "../json/cJSON.h"
#include "../system/atlas.h"
#include "../game/entities.h"
#include "goblin.h"

Entity *goblin;

void initGoblin(void) {
	goblin = spawnEntity();

	goblin->x = 14;
	goblin->y = 29;
	goblin->texture = getAtlasImage("gfx/entities/goblin.png", 1);
	goblin->solid = SOLID_SOLID;
	goblin->alive = ALIVE_ALIVE;
	goblin->facing = FACING_RIGHT;
}
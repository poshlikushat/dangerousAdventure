#include "../common.h"

#include "../game/entities.h"
#include "../game/map.h"
#include "../game/player.h"
#include "../game/fogOfWar.h"
#include "../game/goblin.h"
#include "dungeon.h"

extern App app;
extern Dungeon dungeon;

static void logic(void);
static void draw(void);

void initDungeon(void)
{
	Entity *e;

	initMap();

	initEntities();

	initPlayer();

	initFogOfWar();

	initGoblin();

	dungeon.renderOffset.x = (SCREEN_WIDTH - (MAP_RENDER_WIDTH * TILE_SIZE)) / 2;
	dungeon.renderOffset.y = (SCREEN_HEIGHT - (MAP_RENDER_HEIGHT * TILE_SIZE)) / 2;

	app.delegate.logic = &logic;
	app.delegate.draw = &draw;
}

static void logic(void)
{
	doPlayer();
}

static void draw(void)
{
	drawMap();

	drawEntities();

	drawFogOfWar();
}

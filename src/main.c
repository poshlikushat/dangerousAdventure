#include "common.h"

#include "game/dungeon.h"
#include "main.h"
#include "system/draw.h"
#include "system/init.h"
#include "system/input.h"

App app;
Dungeon dungeon;
Entity *player;

static void logic(void);
static void doFPS(void);

static int fps;
static long nextFPS;

int main(int argc, char *argv[])
{
	long then;

	memset(&app, 0, sizeof(App));

	initSDL();

	initGameSystem();

	initDungeon();

	atexit(cleanup);

	nextFPS = SDL_GetTicks() + 1000;

	while (1)
	{
		then = SDL_GetTicks();

		prepareScene();

		doInput();

		logic();

		app.delegate.draw();

		presentScene();

		/* allow the CPU/GPU to breathe */
		SDL_Delay(1);

		app.deltaTime = LOGIC_RATE * (SDL_GetTicks() - then);

		doFPS();
	}

	return 0;
}

static void logic(void)
{
	double tmpDelta;

	/* don't exceed target logic rate */
	while (app.deltaTime > 1)
	{
		tmpDelta = app.deltaTime;

		app.deltaTime = 1;

		app.delegate.logic();

		app.deltaTime = (tmpDelta - 1);
	}

	app.delegate.logic();
}

static void doFPS(void)
{
	fps++;

	if (SDL_GetTicks() >= nextFPS)
	{
		app.dev.fps = fps;

		fps = 0;

		nextFPS = SDL_GetTicks() + 1000;
	}
}

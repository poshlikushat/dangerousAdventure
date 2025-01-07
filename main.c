#include <string.h>
#include <stdio.h>
#include "init.h"
#include "input.h"
#include "draw.h"
#include "structs.h"

App app;
Entity player;

int main(int argc, char *argv[]) {
	memset(&app, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));

	initSDL();

	player.x = 500;
	player.y = 100;
	player.texture = loadTexture("../assets/mainHero.png");

	if (player.texture == NULL)
	{
		printf("Failed to load texture: %s\n", SDL_GetError());
		exit(1);
	}

	atexit(cleanup);

	while(1) {
		prepareScene();

		doInput();

		blit(player.texture, player.x, player.y);

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
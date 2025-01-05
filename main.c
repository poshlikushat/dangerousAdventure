#include "init.h"
#include "input.h"
#include "draw.h"
#include <string.h>
#include <stdio.h>
#include "structs.h"

App app;

int main(int argc, char *argv[]) {
	memset(&app, 0, sizeof(App));

	initSDL();

	atexit(cleanup);

	while(1) {
		prepareScene();

		doInput();

		presentScene();

		SDL_Delay(16);
	}

	return 0;
}
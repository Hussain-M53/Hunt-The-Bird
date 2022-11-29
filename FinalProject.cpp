#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include "SDL_ttf.h"
#include "Game.h"


using namespace std;

int main(int argc, char* args[])
{
	const int FPS = 60;
	const int frame_delay = 1000 / FPS;
	Uint32 frame_start;
	int frame_time;
	Game* game = Game::getInstance();
	game->initialize("Bird Hunting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,640 , false);

		while (game->running()) {
			frame_start = SDL_GetTicks();

			game->handleEvents();
			game->render();

			frame_time = SDL_GetTicks();

			if (frame_delay > frame_time) {
				SDL_Delay(frame_delay - frame_time);
			}
		}
		
	game->clean();
	return 0;
}


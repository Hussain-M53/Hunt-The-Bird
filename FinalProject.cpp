#include <iostream>
#include <stdlib.h> 
#include "SDL_ttf.h"
#include "Game.h"
#include "Menu.h"
#include "Middleware.h"

using namespace std;

int main(int argc, char* args[])
{

	const int FPS = 60;
	const int frame_delay = 1000 / FPS;
	Uint32 frame_start = 0;
	int frame_time = 0;

	Game* game = Game::getInstance();
	Menu* menu = Menu::getInstance();
	game->initialize("Bird Hunting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Middleware::SCREEN_WIDTH, Middleware::SCREEN_HEIGHT, false);
	string menu_selection = menu->showMenu();
	if (menu_selection != "exit") game->playGameMusic();

		while (game->running() && menu_selection!="exit") {
			frame_start = SDL_GetTicks();

			game->handleEvents();
			game->handleGameChanges();
			game->render();

			frame_time = SDL_GetTicks();

			if (frame_delay > frame_time) {
				SDL_Delay(frame_delay - frame_time);
			}
		}
		
	game->clean();

	return 0;
}


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
	int level = 1;
	

	Game* game = Game::getInstance();
	Menu* menu = Menu::getInstance();
	game->initialize("Bird Hunting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Middleware::SCREEN_WIDTH, Middleware::SCREEN_HEIGHT, false);
	string menu_selection = menu->showMenu();
	if (menu_selection != "exit") {
		game->playGameMusic();
		game->initializeGameStart(menu_selection);
	}

	while (menu_selection != "exit") {
		while (game->running()) {
			frame_start = SDL_GetTicks();

			game->handleEvents();
			if (level == 1) {
				level = game->handleLevelOneChanges();
				if (level == 2) {
					game->startLevelTwo();
				}
			}
			else if (level == 2) {
				level = game->handleLevelTwoChanges();
			}
			
			game->update();
			game->render();

			frame_time = SDL_GetTicks();

			if (frame_delay > frame_time) {
				SDL_Delay(frame_delay - frame_time);
			}
		}
		menu_selection= menu->showMenu();
		game->resetGame(menu_selection);
	}

	return 0;
}


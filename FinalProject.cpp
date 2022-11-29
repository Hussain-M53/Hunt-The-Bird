#include "FinalProject.h"

using namespace std;

int main(int argc, char* args[])
{

	Game* game = Game::getInstance();
	Menu* menu = Menu::getInstance();
	game->initialize("Bird Hunting", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Middleware::SCREEN_WIDTH, Middleware::SCREEN_HEIGHT, false);
	menu->showMenu();

	//	while (game->running()) {
	//		frame_start = SDL_GetTicks();

	//		game->handleEvents();
	//		game->updateChanges();
	//		game->render();

	//		frame_time = SDL_GetTicks();

	//		if (frame_delay > frame_time) {
	//			SDL_Delay(frame_delay - frame_time);
	//		}
	//	}
	//	
	//game->clean();

	return 0;
}


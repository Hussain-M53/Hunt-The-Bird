#include "SDL.h"
#include "Menu.h"
using namespace std;

Menu* Menu::menu_instance = nullptr;

Menu::Menu() {
	isMenu = true;
}

Menu::~Menu() {

}

void Menu::loadMedia() {

}


Menu* Menu::getInstance() {

	if (menu_instance == nullptr) {
		menu_instance = new Menu();
	}
	return menu_instance;
}


bool Menu::checkButtonCollision(int x, int y, SDL_Rect rect) {
	if ((x > rect.x) && (x < rect.x + rect.w)
		&& (y > rect.y) && (y < rect.y + rect.h)) return true;
	else return false;
}

void Menu::showMenu() {

	Mix_HaltMusic();
	TTF_Init();
	TTF_Font* DebugFont = TTF_OpenFont("Fonts/debug_font.otf", 50);
	SDL_Color Color = { 255, 255, 255 ,255 };

	SDL_Event event;

	while (isMenu) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) isMenu = false;
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				//if (checkButtonCollision(x,y,rect)) {}
			}
		}

		SDL_RenderClear(Middleware::renderer);
		SDL_RenderPresent(Middleware::renderer);
	}
}

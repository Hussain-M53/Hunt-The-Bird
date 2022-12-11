#include "SDL.h"
#include "Menu.h"
#include <iostream>
#include "Button.h"
#include "Music.h"
using namespace std;

Menu* Menu::menu_instance = nullptr;



Menu::Menu() {
	isMenu = true;
}

Menu::~Menu() {

}

SDL_Point Menu::getSize(SDL_Texture* texture) {
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}


void Menu::clickSound() {
	Mix_HaltMusic();
	Mix_PlayChannel(-1, Music::getMusicInstance()->getMenuSelect(), 0);
}


Menu* Menu::getInstance() {

	if (menu_instance == nullptr) {
		menu_instance = new Menu();
	}
	return menu_instance;
}


bool Menu::checkButtonCollision(int x, int y, SDL_Rect rect) {
	if ((x > rect.x) && (x < rect.x + rect.w)
		&& (y > rect.y) && (y < rect.y + rect.h))
	{
		return true;
	}
	else return false;
}

string Menu::showMenu() {
	Texture::getInstance();
	string game_state = "";
	Mix_HaltMusic();
	TTF_Font* SpaceFontLarge = TTF_OpenFont("Fonts/debug_font.otf", 100);
	TTF_Font* SpaceFont = TTF_OpenFont("Fonts/debug_font.otf", 40);

	SDL_Rect gSpriteClips[2];
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 64;
	gSpriteClips[0].h = 64;

	gSpriteClips[1].x = 64+22;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 64;
	gSpriteClips[1].h = 64;
	TTF_Init();
	SDL_Rect play_button = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2),((Middleware::SCREEN_HEIGHT / 2) - (2 * gSpriteClips[0].h)),3 * gSpriteClips[0].w,gSpriteClips[0].h * 2 };
	SDL_Rect exit_button = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2),(play_button.y+play_button.h+10),3 * gSpriteClips[0].w,gSpriteClips[0].h * 2 };
	SDL_Rect continue_button = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2),(exit_button.y + exit_button.h + 10),3 * gSpriteClips[0].w,gSpriteClips[0].h * 2 };
	SDL_Color Color = { 255, 255, 255 ,255 };

	SDL_Surface* gameTitleSurface = TTF_RenderText_Solid(SpaceFontLarge, "Hunt The Sky", Color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Middleware::renderer, gameTitleSurface);
	SDL_Point titlePoint = getSize(Message);
	SDL_Rect rect = { (Middleware::SCREEN_WIDTH / 2) - (titlePoint.x / 2),(Middleware::SCREEN_HEIGHT / 4) - (titlePoint.y),titlePoint.x,titlePoint.y };

	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(Music::getMusicInstance() -> getMenuMusic(), -1);
	}
	SDL_Event event;
	bool isMenu = true;
	while (isMenu) {
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				isMenu = false;
				game_state = "exit";
				break;
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (SDL_BUTTON_LEFT == event.button.button) {
					if (checkButtonCollision(x, y, play_button)) {
						clickSound();
						game_state = "new";
						isMenu = false;
						break;
					}
					else if (checkButtonCollision(x, y, exit_button)) {
						clickSound();
						game_state = "exit";
						isMenu = false;
						break;
					}
					else if (checkButtonCollision(x, y, continue_button)) {
						clickSound();
						game_state = "continue";
						isMenu = false;
						break;
					}
				}
			}
			break;
		}
		SDL_Rect menu_screen_rect = {0,0,900,700};
		SDL_RenderClear(Middleware::renderer);
		SDL_RenderCopy(Middleware::renderer, Texture::getInstance()->getmenu_screen_texture(),NULL, &menu_screen_rect);
		SDL_RenderCopy(Middleware::renderer, Message, NULL, &rect);
		Button::getInstance()->display_button("New",play_button);
		Button::getInstance()->display_button("Exit", exit_button);
		Button::getInstance()->display_button("Continue", continue_button);
		SDL_RenderPresent(Middleware::renderer);
	}
	SDL_FreeSurface(gameTitleSurface);
	SDL_DestroyTexture(Texture::getInstance()->getbuttonTexture());
	SDL_DestroyTexture(Texture::getInstance()->getmenu_screen_texture());
	SDL_DestroyTexture(Message);
	Mix_FreeMusic(Music::getMusicInstance() ->getMenuMusic());
	Mix_FreeChunk(Music::getMusicInstance() ->getMenuSelect());
	return game_state;
}


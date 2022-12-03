#include "SDL.h"
#include "Menu.h"
#include <iostream>
using namespace std;

Menu* Menu::menu_instance = nullptr;
SDL_Rect buttonTopLeft, buttonTopMiddle, buttonTopRight, buttonBottomLeft, buttonBottomMiddle, buttonBottomRight;
Mix_Music* menuMusic = NULL;
Mix_Chunk* menuSelect = NULL;
SDL_Texture* buttonTexture;

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

void Menu::loadMedia() {
	menuMusic = Mix_LoadMUS("Music/Menu_Music.mp3");
	menuSelect = Mix_LoadWAV("Music/Sound Effects/blipSelect.wav");
	buttonTexture = Middleware::LoadTexture("Images/buttons.png");
}

void Menu::clickSound() {
	Mix_HaltMusic();
	Mix_PlayChannel(-1, menuSelect, 0);
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

void Menu::display_button(SDL_Rect* gSpriteClips, int position) {
	buttonTopLeft = { position ,((Middleware::SCREEN_HEIGHT - 130) / 2),64,64 };
	SDL_RenderCopyEx(Middleware::renderer, buttonTexture, &gSpriteClips[0], &buttonTopLeft, NULL, NULL, SDL_FLIP_VERTICAL);
	buttonTopMiddle = { position + 63 ,((Middleware::SCREEN_HEIGHT - 132) / 2),65,65 };
	SDL_RenderCopyEx(Middleware::renderer, buttonTexture, &gSpriteClips[1], &buttonTopMiddle, 90, NULL, SDL_FLIP_NONE);
	buttonTopRight = { position + 126,((Middleware::SCREEN_HEIGHT - 130) / 2),64,64 };
	SDL_RenderCopyEx(Middleware::renderer, buttonTexture, &gSpriteClips[0], &buttonTopRight, 180, NULL, SDL_FLIP_NONE);
	buttonBottomLeft = { position ,((Middleware::SCREEN_HEIGHT - 130) / 2) + 63,64,64 };
	SDL_RenderCopyEx(Middleware::renderer, buttonTexture, &gSpriteClips[0], &buttonBottomLeft, NULL, NULL, SDL_FLIP_NONE);
	buttonBottomMiddle = { position + 63,((Middleware::SCREEN_HEIGHT - 130) / 2) + 63,65,65 };
	SDL_RenderCopyEx(Middleware::renderer, buttonTexture, &gSpriteClips[1], &buttonBottomMiddle, -90, NULL, SDL_FLIP_NONE);
	buttonBottomRight = { position + 126,((Middleware::SCREEN_HEIGHT - 130) / 2) + 63,64,64 };
	SDL_RenderCopyEx(Middleware::renderer, buttonTexture, &gSpriteClips[0], &buttonBottomRight, NULL, NULL, SDL_FLIP_HORIZONTAL);

}

string Menu::showMenu() {

	string game_state = "";
	Mix_HaltMusic();
	loadMedia();
	SDL_Texture* buttonTexture = Middleware::LoadTexture("Images/buttons.png");
	TTF_Font* SpaceFont = TTF_OpenFont("Fonts/debug_font.otf", 40);
	TTF_Font* SpaceFontLarge = TTF_OpenFont("Fonts/debug_font.otf", 100);

	SDL_Rect gSpriteClips[2];
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 64;
	gSpriteClips[0].h = 64;

	gSpriteClips[1].x = 64 + 22;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 64;
	gSpriteClips[1].h = 64;
	TTF_Init();
	SDL_Color Color = { 255, 255, 255 ,255 };

	SDL_Surface* gameTitleSurface = TTF_RenderText_Solid(SpaceFontLarge, "Bird Hunting", Color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Middleware::renderer, gameTitleSurface);
	SDL_Point titlePoint = getSize(Message);
	SDL_Rect rect = { (Middleware::SCREEN_WIDTH / 2) - (titlePoint.x / 2),(Middleware::SCREEN_HEIGHT / 4) - (titlePoint.y / 2),titlePoint.x,titlePoint.y };

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(SpaceFont, "New", Color);
	SDL_Rect play_rect = { (Middleware::SCREEN_WIDTH / 2) - 244,((Middleware::SCREEN_HEIGHT - 150) / 2) + 54,100,100 };
	SDL_Texture* playTexture = SDL_CreateTextureFromSurface(Middleware::renderer, surfaceMessage);
	SDL_QueryTexture(playTexture, NULL, NULL, &play_rect.w, &play_rect.h);

	surfaceMessage = TTF_RenderText_Solid(SpaceFont, "Exit", Color);
	SDL_Rect exit_rect = { (Middleware::SCREEN_WIDTH / 2) - 30,((Middleware::SCREEN_HEIGHT - 150) / 2) + 54,100,100 };
	SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(Middleware::renderer, surfaceMessage);
	SDL_QueryTexture(exitTexture, NULL, NULL, &exit_rect.w, &exit_rect.h);

	surfaceMessage = TTF_RenderText_Solid(SpaceFont, "Continue", Color);
	SDL_Rect continue_rect = { (Middleware::SCREEN_WIDTH / 2) + 145,((Middleware::SCREEN_HEIGHT - 150) / 2) + 54,100,100 };
	SDL_Texture* continueTexture = SDL_CreateTextureFromSurface(Middleware::renderer, surfaceMessage);
	SDL_QueryTexture(continueTexture, NULL, NULL, &continue_rect.w, &continue_rect.h);

	bool isMenu = true;
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(menuMusic, -1);
	}
	SDL_Event event;

	while (isMenu) {
		while (SDL_PollEvent(&event) != 0) {
			
				if (event.type == SDL_QUIT) 
				{
				isMenu = false;
				game_state = "exit";
				}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (SDL_BUTTON_LEFT == event.button.button) {
					if (checkButtonCollision(x, y, play_rect)) {
						clickSound();
						game_state = "new";
						isMenu = false;
					}
					else if (checkButtonCollision(x, y, exit_rect)) {
						clickSound();
						game_state = "exit";
						isMenu = false;
					}
					else if (checkButtonCollision(x, y, continue_rect)) {
						clickSound();
						game_state = "continue";
						isMenu = false;
					}
				}

			}
		}

		SDL_RenderClear(Middleware::renderer);
		SDL_RenderCopy(Middleware::renderer, Message, NULL, &rect);
		display_button(gSpriteClips, (Middleware::SCREEN_WIDTH / 2) - 308);
		display_button(gSpriteClips, (Middleware::SCREEN_WIDTH / 2) - 96);
		display_button(gSpriteClips, (Middleware::SCREEN_WIDTH / 2) + 116);
		SDL_RenderCopy(Middleware::renderer, playTexture, NULL, &play_rect);
		SDL_RenderCopy(Middleware::renderer, exitTexture, NULL, &exit_rect);
		SDL_RenderCopy(Middleware::renderer, continueTexture, NULL, &continue_rect);
		SDL_RenderPresent(Middleware::renderer);
	}
	SDL_FreeSurface(gameTitleSurface);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(buttonTexture);
	SDL_DestroyTexture(Message);
	SDL_DestroyTexture(playTexture);
	SDL_DestroyTexture(exitTexture);
	SDL_DestroyTexture(continueTexture);
	Mix_FreeMusic(menuMusic);
	menuMusic = NULL;
	Mix_FreeChunk(menuSelect);
	return game_state;
}


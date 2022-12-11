#include "SDL.h"
#include "Menu.h"
#include <iostream>
#include "Button.h"
#include "Music.h"
#include "SDL_mixer.h"
using namespace std;

Menu* Menu::menu_instance = nullptr;



Menu::Menu() {
	isMenu = true;
	buttonTopLeft = { 0,0,0,0 };
	buttonTopMiddle = { 0,0,0,0 };
	buttonTopRight = { 0,0,0,0 };
	buttonBottomLeft = { 0,0,0,0 };
	buttonBottomMiddle = { 0,0,0,0 };
	buttonBottomRight = { 0,0,0,0 };
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

void Menu::display_button(SDL_Rect* gSpriteClips,int height) {
	buttonTopLeft = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2) ,height,gSpriteClips[0].w,gSpriteClips[0].h};
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonTopLeft, NULL, NULL, SDL_FLIP_VERTICAL);
	buttonTopMiddle = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2) + gSpriteClips[0].w ,height,gSpriteClips[0].w,gSpriteClips[0].h};
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[1], &buttonTopMiddle, 90, NULL, SDL_FLIP_NONE);
	buttonTopRight = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2) + (2*gSpriteClips[0].w),height,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonTopRight, 180, NULL, SDL_FLIP_NONE);
	buttonBottomLeft = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2) ,height+gSpriteClips[0].h,gSpriteClips[0].w,gSpriteClips[0].h};
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonBottomLeft, NULL, NULL, SDL_FLIP_NONE);
	buttonBottomMiddle = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2) + gSpriteClips[0].w ,height + gSpriteClips[0].h,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[1], &buttonBottomMiddle, -90, NULL, SDL_FLIP_NONE);
	buttonBottomRight = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2) + (2 * gSpriteClips[0].w),height + gSpriteClips[0].h,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonBottomRight, NULL, NULL, SDL_FLIP_HORIZONTAL);

}

string Menu::showMenu() {
	Texture::getInstance();
	Music* music = Music::getMusicInstance();
	string game_state = "";
	Mix_HaltMusic();
	TTF_Font* SpaceFont = TTF_OpenFont("Fonts/debug_font.otf", 40);
	TTF_Font* SpaceFontLarge = TTF_OpenFont("Fonts/debug_font.otf", 100);

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
	SDL_Color Color = { 255, 255, 255 ,255 };

	SDL_Surface* gameTitleSurface = TTF_RenderText_Solid(SpaceFontLarge, "Hunt The Sky", Color);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(Middleware::renderer, gameTitleSurface);
	SDL_Point titlePoint = getSize(Message);
	SDL_Rect rect = { (Middleware::SCREEN_WIDTH / 2) - (titlePoint.x / 2),(Middleware::SCREEN_HEIGHT / 4) - (titlePoint.y),titlePoint.x,titlePoint.y };


	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(SpaceFont, "New", Color);
	SDL_Texture* playTexture = SDL_CreateTextureFromSurface(Middleware::renderer, surfaceMessage);
	SDL_Point play_point = getSize(playTexture);
	SDL_Rect play_rect = { (Middleware::SCREEN_WIDTH / 2) - (play_point.x / 2),50 + ((Middleware::SCREEN_HEIGHT / 2) - (2 * gSpriteClips[0].h)-10) - play_point.y/2 + 40,play_point.x,play_point.y};
	SDL_QueryTexture(playTexture, NULL, NULL, &play_rect.w, &play_rect.h);

	surfaceMessage = TTF_RenderText_Solid(SpaceFont, "Exit", Color);
	SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(Middleware::renderer, surfaceMessage);
	SDL_Point exit_point = getSize(exitTexture);
	SDL_Rect exit_rect = { (Middleware::SCREEN_WIDTH / 2) - (exit_point.x / 2) ,50 + (Middleware::SCREEN_HEIGHT / 2) - exit_point.y/2 + 40,exit_point.x,exit_point.y};
	SDL_QueryTexture(exitTexture, NULL, NULL, &exit_rect.w, &exit_rect.h);

	surfaceMessage = TTF_RenderText_Solid(SpaceFont, "Continue", Color);
	SDL_Texture* continueTexture = SDL_CreateTextureFromSurface(Middleware::renderer, surfaceMessage);
	SDL_Point continue_point = getSize(continueTexture);
	SDL_Rect continue_rect = { (Middleware::SCREEN_WIDTH / 2) - (continue_point.x / 2),50 + ((Middleware::SCREEN_HEIGHT / 2) + (2 * gSpriteClips[0].h) - 10) + 40,continue_point.x,continue_point.y };
	SDL_QueryTexture(continueTexture, NULL, NULL, &continue_rect.w, &continue_rect.h);

	bool isMenu = true;
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music-> getMenuMusic(), -1);
	}
	SDL_Rect play_button = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2),50 + ((Middleware::SCREEN_HEIGHT / 2) - (3 * gSpriteClips[0].h) - 10) + 40,3 * gSpriteClips[0].w,gSpriteClips[0].h * 2 };
	SDL_Rect exit_button = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2),50 + ((Middleware::SCREEN_HEIGHT / 2) - (gSpriteClips[0].h)) + 40,3 * gSpriteClips[0].w,gSpriteClips[0].h * 2 };
	SDL_Rect continue_button = { (Middleware::SCREEN_WIDTH / 2) - ((3 * gSpriteClips[0].w) / 2) ,((Middleware::SCREEN_HEIGHT / 2) + (3 * gSpriteClips[0].h) - 70) + 40,3 * gSpriteClips[0].w,gSpriteClips[0].h * 2 };
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
					if (checkButtonCollision(x, y, play_button)) {
						clickSound();
						game_state = "new";
						isMenu = false;
					}
					else if (checkButtonCollision(x, y, exit_button)) {
						clickSound();
						game_state = "exit";
						isMenu = false;
					}
					else if (checkButtonCollision(x, y, continue_button)) {
						clickSound();
						game_state = "continue";
						isMenu = false;
					}
				}

			}
		}
		

		SDL_Rect menu_screen_rect = {0,0,900,700};
		SDL_RenderClear(Middleware::renderer);
		SDL_RenderCopy(Middleware::renderer, Texture::getInstance()->getmenu_screen_texture(),NULL, &menu_screen_rect);
		SDL_RenderCopy(Middleware::renderer, Message, NULL, &rect);
		display_button(gSpriteClips,50+ ((Middleware::SCREEN_HEIGHT / 2) - (3 * gSpriteClips[0].h) - 10) + 40);
		display_button(gSpriteClips,50+ ((Middleware::SCREEN_HEIGHT / 2) - (gSpriteClips[0].h)) + 40);
		display_button(gSpriteClips, ((Middleware::SCREEN_HEIGHT / 2) + (3 * gSpriteClips[0].h) - 70) + 40);
		SDL_RenderCopy(Middleware::renderer, playTexture, NULL, &play_rect);
		SDL_RenderCopy(Middleware::renderer, exitTexture, NULL, &exit_rect);
		SDL_RenderCopy(Middleware::renderer, continueTexture, NULL, &continue_rect);
		SDL_RenderPresent(Middleware::renderer);
	}
	SDL_FreeSurface(gameTitleSurface);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	SDL_DestroyTexture(playTexture);
	SDL_DestroyTexture(exitTexture);
	SDL_DestroyTexture(continueTexture);
	return game_state;
}


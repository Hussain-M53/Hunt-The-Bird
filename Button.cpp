#include "Button.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Texture.h"
#include <SDL_ttf.h>
#include "Menu.h"

using namespace std;

Button* Button::button_instance = nullptr;

Button* Button::getInstance()
{
	if (button_instance == nullptr) button_instance = new Button();
	return button_instance;
}

Button::Button(){

	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 64;
	gSpriteClips[0].h = 64;

	gSpriteClips[1].x = 64 + 22;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 64;
	gSpriteClips[1].h = 64;
}
Button::~Button()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surfaceMessage);
}
void Button::display_text(const char* text,SDL_Rect button_rect) {
	TTF_Font* SpaceFont = TTF_OpenFont("Fonts/debug_font.otf", 40);
	SDL_Color Color = { 255, 255, 255 ,255 };

	surfaceMessage = TTF_RenderText_Solid(SpaceFont, text, Color);
	texture = SDL_CreateTextureFromSurface(Middleware::renderer, surfaceMessage);
	point = Menu::getInstance()->getSize(texture);
	text_rect = { ((button_rect.x + button_rect.w / 2) - (point.x / 2)),(button_rect.y + button_rect.h / 2 - point.y / 2),point.x,point.y };
	SDL_QueryTexture(texture, NULL, NULL, &text_rect.w, &text_rect.h);
	SDL_RenderCopy(Middleware::renderer, texture, NULL, &text_rect);

}
void Button::display_button(const char* text,SDL_Rect rect) {
	buttonTopLeft = { rect.x ,rect.y,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonTopLeft, NULL, NULL, SDL_FLIP_VERTICAL);
	buttonTopMiddle = { rect.x + gSpriteClips[0].w ,rect.y,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[1], &buttonTopMiddle, 90, NULL, SDL_FLIP_NONE);
	buttonTopRight = { rect.x + (2 * gSpriteClips[0].w),rect.y,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonTopRight, 180, NULL, SDL_FLIP_NONE);
	buttonBottomLeft = { rect.x ,rect.y + gSpriteClips[0].h,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonBottomLeft, NULL, NULL, SDL_FLIP_NONE);
	buttonBottomMiddle = { rect.x + gSpriteClips[0].w ,rect.y + gSpriteClips[0].h,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[1], &buttonBottomMiddle, -90, NULL, SDL_FLIP_NONE);
	buttonBottomRight = { rect.x + (2 * gSpriteClips[0].w),rect.y + gSpriteClips[0].h,gSpriteClips[0].w,gSpriteClips[0].h };
	SDL_RenderCopyEx(Middleware::renderer, Texture::getInstance()->getbuttonTexture(), &gSpriteClips[0], &buttonBottomRight, NULL, NULL, SDL_FLIP_HORIZONTAL);
	display_text(text, rect);

}
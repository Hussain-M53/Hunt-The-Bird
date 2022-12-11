#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>


class Button {
	static Button* button_instance;
	SDL_Rect buttonTopLeft, buttonTopMiddle, buttonTopRight, buttonBottomLeft, buttonBottomMiddle, buttonBottomRight;
	SDL_Rect gSpriteClips[2];
	SDL_Surface* surfaceMessage;
	SDL_Texture* texture;
	SDL_Point point;
	SDL_Rect text_rect;
	Button();
	~Button();
public:
	static Button* getInstance();
	void display_text(const char* text,SDL_Rect rect);
	void display_button(const char* text, SDL_Rect rect);
};

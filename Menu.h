#include "SDL.h" 
#include <stdio.h>
#include <vector>
#include "SDL_ttf.h"
#include <string>
#include "GameObject.h"
#include "Middleware.h"
#include "Texture.h"
#pragma once

using namespace std;

class Menu {
private:
	Menu();
	~Menu();
	static Menu* menu_instance;
	bool isMenu;
	Texture* getTexture;

public:
	static Menu* getInstance();
	static SDL_Point getSize(SDL_Texture* texture);
	bool checkButtonCollision(int x, int y, SDL_Rect rect);
	string showMenu();
	void clickSound();
	void loadMedia();
	void display_button(SDL_Rect* gSpriteClips,int height);

};
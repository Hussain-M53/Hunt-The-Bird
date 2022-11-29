#include "SDL.h" 
#include <stdio.h>
#include <vector>
#include "SDL_ttf.h"
#include <string>
#include "GameObject.h"
#include "Middleware.h"
#pragma once

using namespace std;

class Menu {
private:
	Menu();
	~Menu();
	static Menu* menu_instance;
	bool isMenu;

public:
	static Menu* getInstance();
	bool checkButtonCollision(int x, int y, SDL_Rect rect);
	void showMenu();
	void loadMedia();

};
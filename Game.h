#include "SDL.h" 
#include <stdio.h>
#include <vector>
#include "SDL_ttf.h"
#include <string>
#pragma once

using namespace std;

class Game {
private:
	Game();
	~Game();
	static Game* instance;
	bool isRunning;
	SDL_Window* window;

public:
	static SDL_Renderer* renderer;
	static Game* getInstance();
	void initialize(const char* title, int x, int y, int width, int height, bool fullscreen);
	void handleEvents();
	void render();
	void clean();
	bool running();

};
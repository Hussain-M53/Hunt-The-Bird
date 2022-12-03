#include "SDL.h" 
#include <stdio.h>
#include <vector>
#include "SDL_ttf.h"
#include <string>
#include "GameObject.h"
#include "Middleware.h"
#pragma once

using namespace std;

class Game {
private:
	Game();
	~Game();
	static Game* instance;
	bool isRunning;
	SDL_Window* window;
	int game_score;
	int bow_count;
	int prev_score, prev_bows;
	bool isEnemyCreated;

public:
	double static playerX;
	double static playerY;
	static Game* getInstance();
	void loadMedia();
	void initialize(const char* title, int x, int y, int width, int height, bool fullscreen);
	void setPreviousGameState(string state);
	string saveGameStateVariables();
	bool checkCollision(GameObject* game_object_one,GameObject* game_object_two);
	void handleGameChanges();
	SDL_Point getSize(SDL_Texture* texture);
	void updateScore();
	void playGameMusic();
	void resetGame();
	void initializeGameStart();
	void handleEvents();
	void render();
	void clean();
	bool running();

};
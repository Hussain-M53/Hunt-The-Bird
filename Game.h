#include "SDL.h" 
#include <stdio.h>
#include <vector>
#include "SDL_ttf.h"
#include <string>
#include "GameObject.h"
#include "Middleware.h"
#include "Music.h"
#include "Texture.h"
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
	bool isLevelOneBossCreated;
	bool isLevelTwoBossCreated;
	int level_number;
	SDL_Rect Bow_Count_Rect, Score_Rect, Level_Number_Rect, lives_Rect, health_Rect, backgroundRect;
	vector<GameObject*> bird_list;
	vector<GameObject*> egg_list;
	vector<GameObject*> ui_elements_list;
	vector<GameObject*> explosion_list;
	GameObject* bow;
	GameObject* archer;

public:
	int getLevelNumber();
	double static playerX;
	double static playerY;
	static Game* getInstance();
	void loadMedia();
	void initialize(const char* title, int x, int y, int width, int height, bool fullscreen);
	void startLevelTwo();
	void detectCollisions();
	void insertEggs();
	void update();
	bool checkCollision(GameObject* game_object_one,GameObject* game_object_two);
	int handleLevelOneChanges();
	int handleLevelTwoChanges();
	SDL_Point getSize(SDL_Texture* texture);
	void updateScore();
	void playGameMusic();
	void resetGame(string menu_selection);
	void initializeGameStart(string menu_selection);
	void handleEvents();
	void render();
	bool running();
	void saveStatesinFile();
	string saveGameStateVariables();
	void getGamePreviousStates();
	void initializePreviousGameState(string state);

};
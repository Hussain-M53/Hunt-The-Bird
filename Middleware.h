#pragma once
#include "GameObject.h"
#include <vector>
#include <SDL_mixer.h>


class Middleware {
public:
	Middleware();
	static const int SCREEN_WIDTH = 900;
	static const int SCREEN_HEIGHT = 700;
	static const int LEVEL_ONE_BOSS_SCORE = 100;
	static const int LEVEL_TWO_BOSS_SCORE = 300;
	static SDL_Renderer* renderer;
	static int nSpeedCount;
	static SDL_Texture* LoadTexture(const char* filename);
	static string getListStates(vector<GameObject*>& list);
	static string intToString(int value);
	static string doubleToString(double value);
	static string boolToString(bool alive);
	static void render(vector<GameObject*>& list);
	static void clean(vector<GameObject*>& list);
	static void cleanEntireList(vector<GameObject*>& list);
	static void move(vector<GameObject*>& list);
	static void animate(vector<GameObject*>& list);
	static void createExplosion(GameObject* object, SDL_Texture* ExplosionTexture, vector<GameObject*>& explosion_list, Mix_Chunk* sf_explosion);

};
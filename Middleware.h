#pragma once
#include "GameObject.h"
#include <vector>
#include <SDL_mixer.h>


class Middleware {
public:
	Middleware();
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 640;
	static SDL_Texture* LoadTexture(const char* filename);
	static string getListStates(vector<GameObject*>& list);
	static string intToString(int value);
	static string doubleToString(double value);
	static string boolToString(bool alive);
	static void render(vector<GameObject*>& list);
	static void clean(vector<GameObject*>& list);
	static void cleanEntireList(vector<GameObject*>& list);
	static void move(vector<GameObject*>& list, int nSpeedCount);
	static void animate(vector<GameObject*>& list);

};
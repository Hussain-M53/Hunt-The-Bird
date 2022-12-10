#pragma once
#include "SDL.h"
#include <stdio.h>
#include <vector>
#include <string>
#include "GameObject.h"

using namespace std;

class LevelTwo {
private:
	LevelTwo();
	~LevelTwo();
	static LevelTwo* level_two_instance;
public:
	static LevelTwo* getInstance();
	void handleChanges(vector<GameObject*>& ui_elements_list, vector<GameObject*>& bird_list, int& game_score, bool& enemyCreated);
};

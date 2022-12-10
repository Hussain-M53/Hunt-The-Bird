#pragma once
#include "SDL.h"
#include <stdio.h>
#include <vector>
#include <string>
#include "GameObject.h"

using namespace std;

class LevelOne {
private:
	LevelOne();
	~LevelOne();
	static LevelOne* level_one_instance;
public:
	static LevelOne* getInstance();
	void handleChanges(vector<GameObject*>& ui_elements_list, vector<GameObject*>& bird_list, int& game_score, bool& enemyCreated);
};

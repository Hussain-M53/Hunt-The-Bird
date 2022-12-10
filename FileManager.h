#pragma once
#include "SDL.h" 
#include <stdio.h>
#include <vector>
#include <string>
#include "GameObject.h"
#include "Middleware.h"

using namespace std;

class FileManager {
private:
	FileManager();
	~FileManager();
	static FileManager* file_instance;
public:
	static FileManager* getInstance();
	void makeFileWithStates(vector<GameObject*>& bird_list, vector<GameObject*>& egg_list);
	void readFileAndContinue(vector<GameObject*>& bird_list, vector<GameObject*>& egg_list, vector<GameObject*>& ui_elements_list);
};
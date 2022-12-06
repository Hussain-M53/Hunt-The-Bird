#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Cloud : public GameObject {
	double speed;
public:
	Cloud(SDL_Texture* texture, double x, double y);
	void move();
	//void setPreviousGameState(string state);
	//string saveState();
};


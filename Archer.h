#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Archer : public GameObject {
public:
	Archer(SDL_Texture* texture, double x, double y);
	void move();
	string saveState();
	void setPreviousState(string state);
	void setState(string state);
};


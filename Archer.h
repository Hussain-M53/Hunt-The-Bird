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
	void setPreviousGameState(string state);
	void setState(string state);
	bool animate();

};


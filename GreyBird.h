#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Bird.h"

class GreyBird : public Bird {
public:
	GreyBird(SDL_Texture* texture, double x, double y);
	bool animate();
	void setPreviousGameState(string state);
	string saveState();
};


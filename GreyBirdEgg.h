#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Egg.h"

class GreyBirdEgg : public Egg {
public:
	GreyBirdEgg(SDL_Texture* texture, double x, double y);
	void setPreviousGameState(string state);
	string saveState();
};


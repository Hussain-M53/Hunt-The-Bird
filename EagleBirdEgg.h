#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Egg.h"

class EagleBirdEgg : public Egg {
public:
	EagleBirdEgg(SDL_Texture* texture, double x, double y);
	void setPreviousGameState(string state);
	string saveState();
};
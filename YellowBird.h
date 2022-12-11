#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Bird.h"

class YellowBird : public Bird {
	enum animation {
		flyStateStart = 0,
		flyStateEnd = 3,
	};
public:
	YellowBird(SDL_Texture* texture, double x, double y);
	bool animate();
	void setPreviousGameState(string state);
	string saveState();
};


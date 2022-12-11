#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Bird.h"

class RedBird : public Bird {
	enum animation {
		flyStateStart = 0,
		flyStateEnd = 5,
	};
public:
	RedBird(SDL_Texture* texture, double x, double y);
	bool animate();
	void setPreviousGameState(string state);
	string saveState();
};


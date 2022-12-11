#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Bird.h"

class Dragon : public Bird {
	bool moveRight;
	bool moveDown;
	enum animation {
		flyStateStart = 0,
		flyStateEnd = 11,
	};
public:
	Dragon(SDL_Texture* texture, double x, double y);
	bool animate();
	void move();
	void setPreviousGameState(string state);
	string saveState();
};


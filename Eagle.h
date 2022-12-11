#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Bird.h"

class Eagle : public Bird {
	bool moveRight;
	bool moveDown;
	enum animation {
		flyStateStart = 0,
		flyStateEnd = 14,
	};
public:
	Eagle(SDL_Texture* texture, double x, double y);
	void move();
	bool animate();
	void setPreviousGameState(string state);
	string saveState();
};


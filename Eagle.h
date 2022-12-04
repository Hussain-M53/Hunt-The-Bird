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
public:
	Eagle(SDL_Texture* texture, double x, double y);
	void move();
	bool animate();
};


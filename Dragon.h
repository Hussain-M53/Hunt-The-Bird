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
public:
	Dragon(SDL_Texture* texture, double x, double y);
	bool animate();
	void move();
};


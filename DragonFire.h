#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Egg.h"

class DragonFire : public Egg {
	double movX, movY;
public:
	DragonFire(SDL_Texture* texture, double x, double y);
	bool animate();
	void move();
};


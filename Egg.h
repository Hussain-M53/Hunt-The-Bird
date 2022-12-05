#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Egg : public GameObject {
protected:
	double friction = 1.005;
	double ty = 1;
public:
	Egg(SDL_Texture* texture, double x, double y);
	void move();
};


#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Bird : public GameObject {
protected:
	double friction = 1.01;
	double ty = 1;
public:
	Bird(SDL_Texture* texture, double x, double y);
	void move();
};


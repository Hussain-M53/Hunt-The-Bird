#pragma once
#include "SDL.h" 
#include "GameObject.h"
#include "Middleware.h"
#include<iostream>
#include <stdio.h>

class Explosion : public GameObject {
	int mFrame;
public:
	~Explosion();
	Explosion(SDL_Texture* texture, double x, double y);
	void move();
	bool getAlive();
};


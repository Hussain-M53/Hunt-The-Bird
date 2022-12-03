#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Bird : public GameObject {
public:
	Bird(SDL_Texture* texture, double x, double y);
	void move();
};


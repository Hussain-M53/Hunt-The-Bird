#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Egg : public GameObject {
public:
	Egg(SDL_Texture* texture, int x, int y);
	void move();
};


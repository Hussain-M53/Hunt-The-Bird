#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Sun : public GameObject {
public:
	Sun(SDL_Texture* texture, int x, int y);
	void move();
	void render();
};


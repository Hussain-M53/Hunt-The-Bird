#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Cloud : public GameObject {
public:
	Cloud(SDL_Texture* texture, int x, int y);
	void move();
};


#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Bird.h"

class BirdOne : public Bird {
public:
	BirdOne(SDL_Texture* texture, int x, int y);
};


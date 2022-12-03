#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "Egg.h"

class YellowBirdEgg : public Egg {
public:
	YellowBirdEgg(SDL_Texture* texture, double x, double y);
};
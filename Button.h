#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Button : public GameObject {
public:
	Button(SDL_Texture* texture, double x, double y);
};

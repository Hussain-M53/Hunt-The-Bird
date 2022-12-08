#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class HealthBar : public GameObject {
public:
	HealthBar(SDL_Texture* texture, double x, double y);
	void setState(string state);
};

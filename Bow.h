#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>
#include "GameObject.h"

class Bow : public GameObject {
	double movX, movY;
	double mouseX, mouseY;
public:
	Bow(SDL_Texture* texture, double x, double y, double mouseX, double mouseY);
	void move();
};
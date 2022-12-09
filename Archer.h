#pragma once
#include "Middleware.h"
#include "GameObject.h"
#include <SDL.h>
#include<iostream>
#include <stdio.h>

class Archer : public GameObject {
	double ty;
	double gravity_up,gravity_down;
	bool isJumping,jumpDown;
	double groundHeight;
	int count;
	static Archer* archer_instance;
	Archer(SDL_Texture* texture, double x, double y);
public:
	static Archer* getInstance();
	void move();
	string saveState();
	void setPreviousGameState(string state);
	void setState(string state);
	bool animate();
};


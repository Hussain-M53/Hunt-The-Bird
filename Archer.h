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
	int count;
	static Archer* archer_instance;
	Archer(SDL_Texture* texture, double x, double y);
	enum animation {
		stillStateStart = 0,
		stillStateEnd = 5,
		moveStateStart = 6,
		moveStateEnd = 19,
		deadStateStart = 26,
		deadStateEnd = 30,
		shootStateStart = 20,
		shootStateEnd = 24,
		shootLowStateStart = 31,
		shootLowStateEnd = 35,
		jumpStateStart = 36,
		jumpStateEnd = 43,
	};
public:
	static Archer* getInstance();
	void move();
	string saveState();
	void setPreviousGameState(string state);
	void setState(string state);
	bool animate();
	void setGroundHeight(double groundHeight);
};


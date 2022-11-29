#pragma once
#include <stdio.h>
#include "SDL.h"
#include <string>

using namespace std;

class GameObject {
protected:
	SDL_Texture* texture;
	string name;
	bool alive;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	int x_pos;
	int y_pos;
	int health;
	SDL_Point size;

public:

	//constructors and destructors
	GameObject(SDL_Texture* texture, int x, int y);
	~GameObject();

	//getters and setters
	void setAliveToFalse();
	int getX();
	int getY();
	int getHealth();
	bool getAlive();
	string getName();
	SDL_Rect getDstRect();

	//related to saving state
	string saveState();
	void setPreviousState(string state);

	//related to game objects behaviour
	void render();
	void move();

};

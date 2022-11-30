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
	int width;
	int height;
	int lives;

public:

	int x_pos;
	int y_pos;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;

	//constructors and destructors
	GameObject(SDL_Texture* texture, int x, int y);
	~GameObject();

	//getters and setters
	void setAliveToFalse();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	int getLives();
	bool getAlive();
	string getName();
	SDL_Rect getDstRect();

	//related to saving state
	virtual string saveState();
	virtual void setPreviousState(string state);

	//related to game objects behaviour
	void update();
	virtual void render();
	virtual void move();

};

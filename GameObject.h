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
	double angle_in_radian;
	double angle_in_degree;
	string state;
	SDL_RendererFlip flip;

public:

	double x_pos;
	double y_pos;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;

	//constructors and destructors
	GameObject(SDL_Texture* texture, double x, double y);
	~GameObject();

	//getters and setters
	void setAliveToFalse();
	double getX();
	double getY();
	int getWidth();
	int getHeight();
	int getLives();
	bool getAlive();
	string getName();
	string getState();
	virtual void setState(string state);
	SDL_Rect getDstRect();

	//related to saving state
	virtual string saveState();
	virtual void setPreviousState(string state);

	//related to game objects behaviour
	void update();
	void render();
	virtual void move();

};

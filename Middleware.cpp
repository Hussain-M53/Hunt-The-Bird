#include "Middleware.h"
#include <SDL.h> 
#include <SDL_image.h>
#include <iostream>
#include <sstream>
#include "Game.h"

Middleware::Middleware() {}

void Middleware::render(vector<GameObject*>& list) {
	for (int i = 0; i < list.size(); i++) {
		GameObject* gameObject;
		gameObject = list.at(i);
		gameObject->render();
	}
}

void Middleware::clean(vector<GameObject*>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i)->getAlive() == false)
		{
			delete list.at(i);
			list.erase(list.begin() + i);
		}
	}
}

void Middleware::cleanEntireList(vector<GameObject*>& list)
{
	for (int i = 0; i < list.size(); i++)
	{
		list.at(i)->setAliveToFalse();
		list.at(i) = nullptr;
		delete list.at(i);
		list.erase(list.begin() + i);

	}
}

string Middleware::getListStates(vector<GameObject*>& list)
{
	string state = "";
	for (int i = 0; i < list.size(); i++)
	{
		if (list.at(i)->getAlive() == true) {
			state += list.at(i)->saveState();
		}

	}

	return state;
}

void Middleware::move(vector<GameObject*>& list, int nSpeedCount)
{

}

void Middleware::animate(vector<GameObject*>& list) {

}


SDL_Texture* Middleware::LoadTexture(const char* filename) {
	SDL_Surface* tempSurface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	if (texture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
	}
	SDL_FreeSurface(tempSurface);
	return texture;
}

string Middleware::boolToString(bool value) {
	if (value == true) return "1";
	else return "0";
}

string Middleware::doubleToString(double value) {
	stringstream ss;
	ss << value;
	return ss.str();
}

string Middleware::intToString(int value) {
	stringstream ss;
	ss << value;
	return ss.str();
}




#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Bird::Bird(SDL_Texture* texture, int x, int y) :GameObject(texture, x, y) {
	name = "bird";
}


void Bird::move() {
	if (x_pos <= (Middleware::SCREEN_WIDTH + width))
		this->x_pos++;
	else
		alive = false;
}

#include "Egg.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Egg::Egg(SDL_Texture* texture, int x, int y) :GameObject(texture, x, y) {
	name = "egg";
}


void Egg::move() {
	if (x_pos <= (Middleware::SCREEN_WIDTH + width) && y_pos >= 0 && y_pos <= Middleware::SCREEN_HEIGHT + height)
	{
		y_pos++;
	}
	else
		alive = false;
}

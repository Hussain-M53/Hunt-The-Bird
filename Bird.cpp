#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Bird::Bird(SDL_Texture* texture, int x, int y) :GameObject(texture, x, y) {
	name = "bird";
}


void Bird::move() {
	if (x_pos <= (Middleware::SCREEN_WIDTH + width) && y_pos>=0 && y_pos<=Middleware::SCREEN_HEIGHT + height)
	{
		x_pos++;
		if (Middleware::nSpeedCount % 5 == 0) {
			int random = rand() % 2;
			if (random == 0) y_pos++;
			else y_pos--;
		}
	}
	else
		alive = false;
}

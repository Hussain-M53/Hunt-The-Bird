#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Bird::Bird(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "bird";
}


void Bird::move() {
	if ((x_pos <= (Middleware::SCREEN_WIDTH + width) && y_pos >= 0 && y_pos <= Middleware::SCREEN_HEIGHT + height) || state=="die")
	{
		if(state=="still")
		{
			x_pos++;
			if (Middleware::nSpeedCount % 5 == 0) {
				int random = rand() % 2;
				if (random == 0) y_pos++;
				else y_pos--;
			}
		}
		if (state == "die" && y_pos <= Middleware::SCREEN_HEIGHT - 150) {
			y_pos += ty;
			ty *= friction;
		}
	}
	else
	{
		alive = false;
	}
}

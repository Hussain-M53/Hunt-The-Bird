#include "Cloud.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Cloud::Cloud(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "cloud";
}


void Cloud::move() {
	if (x_pos <= (Middleware::SCREEN_WIDTH + width)) {
		if (Middleware::nSpeedCount % 5 == 0) this->x_pos++;
	}
	else
		alive = false;
}

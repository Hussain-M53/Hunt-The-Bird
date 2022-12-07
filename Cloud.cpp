#include "Cloud.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Cloud::Cloud(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "cloud";
	width = 150;
	height = 150;
	int randomCloudSelection = rand() % 8;
	src_rect = { randomCloudSelection*width,0,width,height };
	dst_rect = { int(x),int(y),width,height };
	speed = 1 + rand() % 1;
	
}


void Cloud::move() {
	if (x_pos <= (Middleware::SCREEN_WIDTH + width)) {
		if (Middleware::nSpeedCount % 5 == 0) this->x_pos+= speed;
	}
	else
		alive = false;
}

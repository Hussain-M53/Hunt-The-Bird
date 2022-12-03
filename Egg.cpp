#include "Egg.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Egg::Egg(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	src_rect = { 0,0,32,32 };
	dst_rect = { int(x) , int(y) , 32, 32 };
	name = "egg";
}


void Egg::move() {
	if (x_pos <= (Middleware::SCREEN_WIDTH + width) && y_pos >= 0 && y_pos <= Middleware::SCREEN_HEIGHT + height)
	{
		y_pos += ty;
		ty *= friction;


	}
	else
		alive = false;
}

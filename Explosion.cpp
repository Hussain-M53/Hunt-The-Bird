#include "Explosion.h"
#include <math.h>


Explosion:: ~Explosion() {
	mFrame = 0;
}

Explosion::Explosion(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y)
{
	name = "explosion";
	width = 64;
	height = 64;
	src_rect.h = height;
	src_rect.w = width;
	dst_rect.w = width;
	dst_rect.h = height;
	//Initialize animation
	mFrame = rand() % 50;
	angle_in_radian = 0;
}

void Explosion::move() {
	this->y_pos -= 1;
	this->x_pos += 2 * sin(angle_in_radian);
	angle_in_radian += 0.5;
	mFrame++;

}

bool Explosion::getAlive() {
	return mFrame < 100;
}
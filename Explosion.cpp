#include "Explosion.h"
#include <math.h>


Explosion:: ~Explosion() {
	mFrame = 0;
}

Explosion::Explosion(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y)
{
	name = "explosion";
	src_rect.h = 64;
	src_rect.w = 64;
	dst_rect.w = 64;
	dst_rect.h = 64;
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
	return mFrame < 50;
}
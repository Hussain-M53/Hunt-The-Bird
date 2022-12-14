#include "Explosion.h"
#include <math.h>


Explosion:: ~Explosion() {
	mFrame = 0;
}

Explosion::Explosion(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y)
{
	name = "explosion";
	int random =  1+ rand() % 3;
	if (random == 2) {
		src_rect.x = 86;
		src_rect.y = 0;
	}
	else if(random == 3) {
		src_rect.x = 172;
		src_rect.y = 0;
	} 
	width = 16;
	height = 16;

	height = 16;
	width = 16;
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
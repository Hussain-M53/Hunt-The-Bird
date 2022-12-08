#include "Explosion.h"
#include <math.h>


Explosion:: ~Explosion() {
	mFrame = 0;
}

Explosion::Explosion(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y)
{
	name = "explosion";
<<<<<<< HEAD
	int random =  1+ rand() % 3;
	if (random == 2) {
		src_rect.x = 86;
		src_rect.y = 0;
	}
	else if(random == 3) {
		src_rect.x = 172;
		src_rect.y = 0;
	} 
	src_rect.h = 64;
	src_rect.w = 64;
	dst_rect.w = 16;
	dst_rect.h = 16;
=======
	width = 64;
	height = 64;
	src_rect.h = height;
	src_rect.w = width;
	dst_rect.w = width;
	dst_rect.h = height;
>>>>>>> ec1dfcae2b064d7d781d412a1a20566a2be2eb66
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
#include "DragonFire.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Game.h"
#define PI 3.14159265

using namespace std;


DragonFire::DragonFire(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	width = 50;
	height = 100;
	src_rect = { 0,0,width,100 };
	dst_rect = { int(x),int(y),width,100 };
	name = "dragon_fire";
	movX = Game::playerX - x_pos;
	movY = Game::playerY - y_pos;
	angle_in_radian = atan2(movY, movX);
	angle_in_degree = (angle_in_radian * 180 / PI) +270;
}

bool DragonFire::animate() {
	if (src_rect.x == 15 * width) {
		src_rect.x = 0;
	}
	else {
		src_rect.x += width;
	}
	return false;
}

void DragonFire::move() {
	if (x_pos >= -width && y_pos >= -height && y_pos <= Middleware::SCREEN_HEIGHT-height) {
		this->x_pos += cos(angle_in_radian);
		this->y_pos += sin(angle_in_radian);
	}
	else {
		alive = false;
	}
}
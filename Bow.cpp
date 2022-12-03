#include "GreyBird.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Bow.h"
#include <math.h>
#include <sstream>
#include <iostream>
#include "Game.h"
#define PI 3.14159265

using namespace std;


Bow::Bow(SDL_Texture* texture, double x, double y, double mouseX,double mouseY) :GameObject(texture, x, y) {
	movX = mouseX - x_pos;
	movY = mouseY- y_pos;
	angle_in_radian = atan2(movY, movX);
	angle_in_degree = (angle_in_radian * 180 / PI) - 180;
	name = "bow";
}


void Bow::move() {
	if (x_pos >= -getWidth() && y_pos >= -getHeight() && y_pos <= Middleware::SCREEN_HEIGHT-getHeight()) {
		this->x_pos += 2 * cos(angle_in_radian);
		this->y_pos += 2 *sin(angle_in_radian);
	}
	else {
		alive = false;
	}
}
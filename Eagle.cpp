#include "Bird.h"
#include "Eagle.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Eagle::Eagle(SDL_Texture* texture, double x, double y) :Bird(texture, x, y) {
	src_rect = { 0,0,100,100 };
	dst_rect = { int(x),int(y),100,100 };
	name = "eagle";
	lives = 1;
	moveRight = true;
	moveDown = false;
	width = 100;
	height = 100;
}

void Eagle::move() {
	if (y_pos >= Middleware::SCREEN_HEIGHT - dst_rect.h) {
		y_pos = 0;
	}


	if (moveDown) {
		flip = SDL_FLIP_VERTICAL;
		this->y_pos += 3;
		if (int(y_pos) % 5 == 0) {
			moveDown = false;
		}
	}
	else {
		if (moveRight) {
			flip = SDL_FLIP_HORIZONTAL;;
			x_pos--;
			if (x_pos <= 10) {
				moveDown = true;
				moveRight = false;
			}
		}
		else {
			flip = SDL_FLIP_NONE;
			x_pos++;
			if (x_pos >= Middleware::SCREEN_WIDTH - dst_rect.w) {
				moveDown = true;
				moveRight = true;
			}
		}
	}
}

bool Eagle::animate(){

		if (src_rect.x >= 15 * width) {
			src_rect.x = 0;
		}
		else {
			src_rect.x += width;
		}
	return false;
}

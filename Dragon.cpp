#include "Bird.h"
#include "Dragon.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Bird.h"

using namespace std;


Dragon::Dragon(SDL_Texture* texture, double x, double y) :Bird(texture, x, y) {
	src_rect = { 0,0,200,200 };
	dst_rect = { int(x),int(y),200,200 };
	name = "dragon";
	width = 200;
	height = 200;
}

bool Dragon::animate() {
		if (src_rect.x >= 11 * width) {
			src_rect.x = 0;
		}
		else {
			src_rect.x += width;
		}
	
	return false;
}

void Dragon::move() {
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

#include "Archer.h"
#include <sstream>
#include <iostream>
using namespace std;


Archer::Archer(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	src_rect = { 0,0,120,120 };
	dst_rect = { int(x),int(y),120,120 };
	name = "archer";
	width = 120;
	height = 120;
}


void Archer::move() {
	if (state == "movingright") {
		x_pos++;
	}
	if (state == "movingleft") {
		x_pos--;
	}
}

string Archer::saveState() {
	return"";
}

void Archer::setPreviousState(string state) {

}
void Archer::setState(string state)
{

	if (state == "still") {
		src_rect.x = 0;
	}
	if (state == "movingleft") {
		flip = SDL_FLIP_HORIZONTAL;
		src_rect.x = 720;
	}
	if (state == "movingright") {
		flip = SDL_FLIP_NONE;
		src_rect.x = 720;
	}
	if (state == "dead") {
		src_rect.x = 3120;
	}
	if (state == "shootright") {
		flip = SDL_FLIP_NONE;
		src_rect.x = 2400;
	}
	if (state == "shootleft") {
		src_rect.x = 2400;
		flip = SDL_FLIP_HORIZONTAL;
	}
	this->state = state;
}

bool Archer::animate() {
		if (state == "still") {
			if (src_rect.x == 5 * width) {
				src_rect.x = 0;
			}
			else {
				src_rect.x += width;
			}
		}
		if (state == "movingleft" || state == "movingright") {
			if (src_rect.x == 19 * width) {
				src_rect.x = 6 * width;
			}
			else {
				src_rect.x += width;
			}
		}
		if (state == "dead") {
			if (src_rect.x == 30 * width) {
				src_rect.x = 30 * width;
				//isRunning = false;
			}
			else {
				src_rect.x += width;
			}
		}
		if (state == "shootright" || state == "shootleft") {
			if (src_rect.x == 24 * width) {
				return true;
			}
			else {
				src_rect.x += width;
			}
		}
		return false;
}
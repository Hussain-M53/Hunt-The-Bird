#include "Archer.h"
#include <sstream>
#include <iostream>
using namespace std;


Archer::Archer(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	src_rect = { 0,0,120,120 };
	dst_rect = { int(x),int(y),120,120 };
	name = "archer";
}


void Archer::move() {
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
	if (state == "shoot") {
		src_rect.x = 2400;
	}
	this->state = state;
}
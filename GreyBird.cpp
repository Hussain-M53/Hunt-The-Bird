#include "GreyBird.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Bird.h"

using namespace std;


GreyBird::GreyBird(SDL_Texture* texture, double x, double y) :Bird(texture, x, y) {
	src_rect = { 0,0,64,68 };
	dst_rect = { int(x),int(y),64,68 };
	width = 64;
	height = 68;
	name = "grey_bird";
}

bool GreyBird::animate() {
	if (state == "die") {
		src_rect.x = 0;
	}
	else if (src_rect.x == 3 * width) {
		src_rect.x = 0;
	}
	else {
		src_rect.x += width;
	}
	return false;
}

string GreyBird::saveState() {
	//Format:
	// 	<GreyBird>
	//	xpos
	//	ypos
	//	ty
	//	src_rect.x
	//state

	string state = "<GreyBird>\n";
	state += Middleware::doubleToString(x_pos) + "\n";
	state += Middleware::doubleToString(y_pos) + "\n";
	state += Middleware::doubleToString(ty) + "\n";
	state += Middleware::intToString(src_rect.x) + "\n";
	state += this->state + "\n";
	return state.c_str();
}

void GreyBird::setPreviousGameState(string state) {
	istringstream f(state);
	string line;
	int counter = 0;
	while (getline(f, line)) {
		if (counter == 0) x_pos = stod(line);
		if (counter == 1) y_pos = stod(line);
		if (counter == 2) ty = stod(line);
		if (counter == 3) src_rect.x = stoi(line);
		if (counter == 4) this->state = line;
		counter++;
	}
}

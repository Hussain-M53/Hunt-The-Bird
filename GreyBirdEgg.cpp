#include "GreyBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


GreyBirdEgg::GreyBirdEgg(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	name = "grey_bird_egg";
}

string GreyBirdEgg::saveState() {
	//Format:
	// 	<GreyBirdEgg>
	//	xpos
	//	ypos
	//	ty
	//	src_rect.x
	//state

	string state = "<GreyBirdEgg>\n";
	state += Middleware::doubleToString(x_pos) + "\n";
	state += Middleware::doubleToString(y_pos) + "\n";
	state += Middleware::doubleToString(ty) + "\n";
	state += this->state + "\n";
	return state.c_str();
}

void GreyBirdEgg::setPreviousGameState(string state) {
	istringstream f(state);
	string line;
	int counter = 0;
	while (getline(f, line)) {
		if (counter == 0) x_pos = stod(line);
		if (counter == 1) y_pos = stod(line);
		if (counter == 2) ty = stod(line);
		if (counter == 3) this->state = line;
		counter++;
	}
}
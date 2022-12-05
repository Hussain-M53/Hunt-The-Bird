#include "RedBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


RedBirdEgg::RedBirdEgg(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	name = "red_bird_egg";
}
string RedBirdEgg::saveState() {
	//Format:
	// 	<RedBird>
	//	xpos
	//	ypos
	//	ty
	//	src_rect.x
	//state

	string state = "<RedBirdEgg>\n";
	state += Middleware::doubleToString(x_pos) + "\n";
	state += Middleware::doubleToString(y_pos) + "\n";
	state += Middleware::doubleToString(ty) + "\n";
	state += this->state + "\n";
	return state.c_str();
}

void RedBirdEgg::setPreviousGameState(string state) {
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

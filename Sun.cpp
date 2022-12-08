#include "Sun.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Sun::Sun(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "sun";
}


void Sun::move() {
	angle_in_degree += 0.025;
}

string Sun::saveState() {

	//Format:
	// 	<Sun>
	//	xpos
	//	ypos
	// src_rect.x
	//speed

	string state = "<Sun>\n";
	state += Middleware::doubleToString(x_pos) + "\n";
	state += Middleware::doubleToString(y_pos) + "\n";
	state += Middleware::intToString(src_rect.x) + "\n";
	state += Middleware::doubleToString(angle_in_degree) + "\n";
	return state.c_str();

}

void Sun::setPreviousGameState(string state) {
	istringstream f(state);
	string line;
	int counter = 0;
	while (getline(f, line)) {
		if (counter == 0) x_pos = stod(line);
		if (counter == 1) y_pos = stod(line);
		if (counter == 2) src_rect.x = stoi(line);
		if (counter == 3) angle_in_degree = stod(line);
		counter++;
	}
}
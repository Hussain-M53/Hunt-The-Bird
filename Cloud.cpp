#include "Cloud.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Cloud::Cloud(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "cloud";
	width = 150;
	height = 150;
	int randomCloudSelection = rand() % 8;
	src_rect = { randomCloudSelection*width,0,width,height };
	dst_rect = { int(x),int(y),width,height };
	speed = 1 + rand() % 1;
	
}


void Cloud::move() {
	if (x_pos <= (Middleware::SCREEN_WIDTH + width)) {
		if (Middleware::nSpeedCount % 5 == 0) this->x_pos+= speed;
	}
	else
		alive = false;
}
string Cloud::saveState() {

	//Cloud:
	// 	<Cloud>
	//	xpos
	//	ypos
	// src_rect.x
	//speed

	string state = "<Cloud>\n";
	state += Middleware::doubleToString(x_pos) + "\n";
	state += Middleware::doubleToString(y_pos) + "\n";
	state += Middleware::intToString(src_rect.x) + "\n";
	state += Middleware::doubleToString(speed) + "\n";
	return state.c_str();

}

void Cloud::setPreviousGameState(string state) {
	istringstream f(state);
	string line;
	int counter = 0;
	while (getline(f, line)) {
		if (counter == 0) x_pos = stod(line);
		if (counter == 1) y_pos = stod(line);
		if (counter == 2) src_rect.x = stoi(line);
		if (counter == 3) speed = stod(line);
		counter++;
	}
}

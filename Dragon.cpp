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
	lives = 8;
	moveRight = true;
	moveDown = false;
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
			state = "movingright";
			flip = SDL_FLIP_HORIZONTAL;;
			x_pos--;
			if (x_pos <= 10) {
				moveDown = true;
				moveRight = false;
			}
		}
		else {
			state = "movingleft";
			flip = SDL_FLIP_NONE;
			x_pos++;
			if (x_pos >= Middleware::SCREEN_WIDTH - dst_rect.w) {
				moveDown = true;
				moveRight = true;
			}
		}
	}
}


string Dragon::saveState() {

	//Format:
	// 	<Dragon>
	//	xpos
	//	ypos
	// src_rect.x
	// state
	// angleDegree
	//alive
	//moveRight
	//moveDown

	string state = "<Dragon>\n";
	state += Middleware::doubleToString(x_pos) + "\n";
	state += Middleware::doubleToString(y_pos) + "\n";
	state += Middleware::intToString(src_rect.x) + "\n";
	state += Middleware::doubleToString(angle_in_radian) + "\n";
	state += Middleware::doubleToString(angle_in_degree) + "\n";
	state += Middleware::intToString(lives) + "\n";
	state += this->state + "\n";
	state += Middleware::boolToString(alive) + "\n";
	state += Middleware::boolToString(moveRight) + "\n";
	state += Middleware::boolToString(moveDown) + "\n";
	return state.c_str();

}

void Dragon::setPreviousGameState(string state) {
	istringstream f(state);
	string line;
	int counter = 0;
	while (getline(f, line)) {
		if (counter == 0) x_pos = stod(line);
		if (counter == 1) y_pos = stod(line);
		if (counter == 2) src_rect.x = stoi(line);
		if (counter == 3) angle_in_radian = stod(line);
		if (counter == 4) angle_in_degree = stod(line);
		if (counter == 5) lives = stoi(line);
		if (counter == 6) this->state = line;
		if (counter == 7) {
			if (line == "1") {
				alive = true;
			}
			else alive = false;
		}
		if (counter == 8) {
			if (line == "1") moveRight = true;
			else moveRight = false;
		}
		if (counter == 9) {
			if (line == "1") moveDown = true;
			else moveDown = false;
		}
		counter++;
	}
}
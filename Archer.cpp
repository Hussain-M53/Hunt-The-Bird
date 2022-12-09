#include "Archer.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Game.h"

using namespace std;

Archer* Archer::archer_instance = nullptr;

Archer* Archer::getInstance() {

	Texture* getTexture = new Texture();

	if (archer_instance == nullptr) 
	archer_instance = new Archer(getTexture->LoadTexture("Images/archer.png"),0,Middleware::LEVEL_ONE_GROUND_HEIGHT);

	if (Game::getInstance()->getLevelNumber() == 1) {
		archer_instance = new Archer(getTexture->LoadTexture("Images/archer.png"), 0, Middleware::LEVEL_ONE_GROUND_HEIGHT);
	}
	else if (Game::getInstance()->getLevelNumber() == 2)
		archer_instance = new Archer(getTexture->LoadTexture("Images/archer.png"), 0, Middleware::LEVEL_TWO_GROUND_HEIGHT);
	
	return archer_instance;
}

Archer::Archer(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	src_rect = { 0,0,120,120 };
	dst_rect = { int(x),int(y),120,120 };
	name = "archer";
	width = 120;
	height = 120;
	ty = 3.5;
	gravity_up = 0.98;
	gravity_down = 1.02;
	jumpDown = false;
	isJumping = false;
	groundHeight = y;
	lives = 5;
}


void Archer::move() {
	if (x_pos >= -width/2 && x_pos <= Middleware::SCREEN_WIDTH - width/2) {
		if (state == "movingright") {
			x_pos += 1.5;
		}
		if (state == "movingleft") {
			x_pos -= 1.5;
		}
		if (isJumping || y_pos < groundHeight)
		{
			if (ty > 0.1 && jumpDown == false) {

				y_pos -= ty;
				ty *= gravity_up;
			}

			else {
				jumpDown = true;
				y_pos += ty;
				ty *= gravity_down;
				if (y_pos >= groundHeight) {
					y_pos = groundHeight;
					ty = 3.5;
					jumpDown = false;
					isJumping = false;
					setState("still");
				}
			}
		}
	}
	if (x_pos < -double(width / 2)) x_pos++;
	if (x_pos > Middleware::SCREEN_WIDTH - double(width/2)) x_pos--;
}
	

string Archer::saveState() {
	//Format:
// 	<Archer>
//	xpos
// ypos
// src_rect.x
// ty
// isJumping
// jumpDown


	string state = "<Archer>\n";
	state += Middleware::doubleToString(x_pos) + "\n";
	state += Middleware::doubleToString(y_pos) + "\n";
	state += Middleware::intToString(src_rect.x) + "\n";
	state += Middleware::doubleToString(ty) + "\n";
	state += Middleware::boolToString(isJumping) + "\n";
	state += Middleware::boolToString(jumpDown) + "\n";
	state += this->state + "\n";
	return state.c_str();
}

void Archer::setPreviousGameState(string state) {
	istringstream f(state);
	string line;
	int counter = 0;
	while (getline(f, line)) {
		if (counter == 0) x_pos = stod(line);
		if (counter == 1) y_pos = stod(line);
		if (counter == 2) src_rect.x = stoi(line);
		if (counter == 3) ty = stod(line);
		if (counter == 4) {
			if (line == "1") {
				isJumping = true;
			}
			else {
				isJumping = false;
			}
		}
		if (counter == 5) {
			if (line == "1") {
				jumpDown = true;
			}
			else {
				jumpDown = false;
			}
		}

		if (counter == 6) this->state = line;
		counter++;
	}
}
void Archer::setState(string state)
{

		this->state = state;
	

	if (state == "still") {
		src_rect.x = 0;
	}
	if (state == "movingleft") {
		flip = SDL_FLIP_HORIZONTAL;
		src_rect.x = 6 * width;
		if (isJumping) {
			src_rect.x = 36 * width;
		}
		
	}
	if (state == "movingright") {
		flip = SDL_FLIP_NONE;
		src_rect.x = 6 * width;
		if (isJumping) {
			src_rect.x = 36 * width;
		}
	}
	if (state == "dead") {
		src_rect.x = 26 * width;
	}
	if (state == "shootright") {
		flip = SDL_FLIP_NONE;
		src_rect.x = 20  *width;
	}
	if (state == "shootleft") {
		src_rect.x = 20 * width;
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (state == "shootlowleft") {
		src_rect.x = 31 * width;
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (state == "shootlowright") {
		src_rect.x = 31 * width;
		flip = SDL_FLIP_NONE;
	}
	if (state == "jump") {
		src_rect.x = 36 * width;
		isJumping = true;
	}
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
		else if ((state == "movingleft" || state == "movingright")) {
			if (src_rect.x == 19 * width) {
				src_rect.x = 6 * width;
			}
			else {
				src_rect.x += width;
			}
		}
		else if (state == "dead") {
			if (src_rect.x == 30 * width) {
				src_rect.x = 30 * width;
				//isRunning = false;
			}
			else {
				src_rect.x += width;
			}
		}
		else if (state == "shootright" || state == "shootleft") {
			if (src_rect.x == 24 * width) {
				return true;
			}
			else {
				src_rect.x += width;
			}
		}
		else if (state == "shootlowright" || state == "shootlowleft") {
			if (src_rect.x == 35 * width) {
				return true;
			}
			else {
				src_rect.x += width;
			}
		}
		else if (state == "jump") {
			if (src_rect.x == 43 * width) {
				src_rect.x = 43 * width;
			}
			else {
				src_rect.x += width;
			}
		}
		return false;
}

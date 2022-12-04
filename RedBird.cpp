#include "RedBird.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


RedBird::RedBird(SDL_Texture* texture, double x, double y) :Bird(texture, x, y) {
	src_rect = { 0,0,64,56 };
	dst_rect = { int(x),int(y),64,56 };
	width = 64;
	height = 56;
	name = "red_bird";
}

bool RedBird::animate() {
		if (state == "die") {
			src_rect.x = 0;
		}
		if (src_rect.x == 5 * width) {
			src_rect.x = 0;
		}
		else {
			src_rect.x += width;
		}
	return false;
	}
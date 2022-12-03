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

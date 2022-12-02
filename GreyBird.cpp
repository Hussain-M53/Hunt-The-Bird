#include "GreyBird.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Bird.h"

using namespace std;


GreyBird::GreyBird(SDL_Texture* texture, int x, int y) :Bird(texture, x, y) {
	src_rect = { 0,0,64,68 };
	dst_rect = { x,y,64,68 };
	name = "grey_bird";
}

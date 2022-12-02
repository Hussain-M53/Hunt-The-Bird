#include "YellowBird.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


YellowBird::YellowBird(SDL_Texture* texture, int x, int y) :Bird(texture, x, y) {
	src_rect = { 0,0,64,56 };
	dst_rect = { x,y,64,56 };
	name = "yellow_bird";
}

#include "BirdOne.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"
#include "Bird.h"

using namespace std;


BirdOne::BirdOne(SDL_Texture* texture, int x, int y) :Bird(texture, x, y) {
	src_rect = { 0,0,64,58 };
	dst_rect = { x,y,64,58 };
	name = "bird_one";
}

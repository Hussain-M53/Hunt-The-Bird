#include "Bird.h"
#include "Eagle.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Eagle::Eagle(SDL_Texture* texture, int x, int y) :Bird(texture, x, y) {
	src_rect = { 0,0,100,151 };
	dst_rect = { x,y,100,151 };
	name = "eagle";
}

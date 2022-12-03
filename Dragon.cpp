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
}

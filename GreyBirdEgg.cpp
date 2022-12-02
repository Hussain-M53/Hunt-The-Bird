#include "GreyBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


GreyBirdEgg::GreyBirdEgg(SDL_Texture* texture, int x, int y) :Egg(texture, x, y) {
	src_rect = { 0,0,64,64 };
	dst_rect = { x,y,64,64 };
	name = "grey_bird_egg";
}

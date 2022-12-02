#include "YellowBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


YellowBirdEgg::YellowBirdEgg(SDL_Texture* texture, int x, int y) :Egg(texture, x, y) {
	src_rect = { 0,0,64,64 };
	dst_rect = { x,y,64,64 };
	name = "yellow_bird_egg";
}

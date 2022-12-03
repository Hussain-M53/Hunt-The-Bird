#include "YellowBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


YellowBirdEgg::YellowBirdEgg(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	name = "yellow_bird_egg";
}

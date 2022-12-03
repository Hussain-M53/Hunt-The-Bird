#include "GreyBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


GreyBirdEgg::GreyBirdEgg(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	name = "grey_bird_egg";
}

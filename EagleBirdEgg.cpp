#include "EagleBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


EagleBirdEgg::EagleBirdEgg(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	name = "eagle_bird_egg";
}

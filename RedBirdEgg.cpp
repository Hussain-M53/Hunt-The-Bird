#include "RedBirdEgg.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


RedBirdEgg::RedBirdEgg(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	name = "red_bird_egg";
}

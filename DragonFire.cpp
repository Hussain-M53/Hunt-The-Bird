#include "DragonFire.h"
#include "Bird.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


DragonFire::DragonFire(SDL_Texture* texture, double x, double y) :Egg(texture, x, y) {
	name = "dragon_fire";
}

bool DragonFire::animate() {
	return false;
}

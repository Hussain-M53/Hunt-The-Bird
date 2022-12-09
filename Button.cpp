#include "Button.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Button::Button(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "button";

}

#include "Button.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Button::Button(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "health_bar";
	width = 169;
	height = 52;
	src_rect = { 0,0,width,height };
	dst_rect = { int(x),int(y),width,height };

}

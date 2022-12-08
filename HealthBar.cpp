#include "HealthBar.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


HealthBar::HealthBar(SDL_Texture* texture, double x, double y) :GameObject(texture, x, y) {
	name = "health_bar";
	width = 169;
	height = 52;
	src_rect = { 0,0,width,height };
	dst_rect = { int(x),int(y),width,height };

}

void HealthBar::setState(string state) {
	if (state == "1") src_rect.x = 676;
	if (state == "2") src_rect.x = 507;
	if (state == "3") src_rect.x = 338;
	if (state == "4") src_rect.x = 169;
	if (state == "5") src_rect.x = 0;

}

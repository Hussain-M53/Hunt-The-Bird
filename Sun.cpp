#include "Sun.h"
#include <sstream>
#include <iostream>
#include "Middleware.h"

using namespace std;


Sun::Sun(SDL_Texture* texture, int x, int y) :GameObject(texture, x, y) {
	name = "sun";
}


void Sun::move() {
	angle_in_degree += 0.05;
}

void Sun::render() {
	SDL_RenderCopyEx(Middleware::renderer, texture, &src_rect, &dst_rect, angle_in_degree, NULL, SDL_FLIP_NONE);
}

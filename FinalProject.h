#pragma once
#include <iostream>
#include <stdlib.h> 
#include "SDL_ttf.h"
#include "Game.h"
#include "Menu.h"
#include "Middleware.h"

class FinalProject {

	const int FPS = 60;
	const int frame_delay = 1000 / FPS;
	Uint32 frame_start = 0;
	int frame_time = 0;
};
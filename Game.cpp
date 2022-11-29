#include "Game.h"
#include <SDL_mixer.h>

using namespace std;

Game* Game::instance = 0;
SDL_Renderer* Game::renderer = nullptr;

Game::Game() {
	window = nullptr;
	isRunning = false;
}

Game::~Game() {

}


Game* Game::getInstance() {

	if (instance == nullptr) {
		instance = new Game();
	}
	return instance;

}

void Game::initialize(const char* title, int x, int y, int width, int height, bool fullscreen) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		isRunning = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow(title, x, y, width, height, 0);
		TTF_Init();
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			isRunning = false;
		}
		else
		{
			//Get window surface
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			isRunning = true;
		}

		//Initialize SDL_mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			isRunning = false;
		}
		isRunning = true;

	}
}

void Game::loadMedia() {

}

void Game::handleEvents() {

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {

		if (event.type == SDL_QUIT)
			isRunning = false;
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				break;
			case SDLK_b:
				break;
				}
			}
		}
	}

void Game::render() {

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}


void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Game::running() {
	return isRunning;
}
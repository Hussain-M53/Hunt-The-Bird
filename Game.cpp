#include "Game.h"
#include <SDL_mixer.h>

using namespace std;

Game* Game::instance = nullptr;


Game::Game() {
	window = nullptr;
	isRunning = false;
	nSpeedCount = 0;
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
			Middleware::renderer = SDL_CreateRenderer(window, -1, 0);
			if (Middleware::renderer) {
				SDL_SetRenderDrawColor(Middleware::renderer, 255, 255, 255, 255);
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

void Game::setPreviousGameState(string state) {}
string Game::saveGameStateVariables() {

	string state = "<GameState>\n";
	//state += "";
	return state.c_str();
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

void Game ::updateChanges() {

}

bool Game::checkCollision(GameObject* game_object_one, GameObject game_object_two)
{

	SDL_Rect rectOne = game_object_one->getDstRect();
	SDL_Rect rectTwo = game_object_one->getDstRect();

	int rectOneLeft = rectOne.x;
	int rectOneRight = rectOne.x + rectOne.w;
	int rectOneTop = rectOne.y;
	int rectOneBottom = rectOne.y + rectOne.h;

	int rectTwoLeft = rectTwo.x;
	int rectTwoRight = rectTwo.x + rectTwo.w;
	int rectTwoTop = rectTwo.y;
	int rectTwoBottom = rectTwo.y + rectTwo.h;

	if ((rectOneBottom <= rectTwoTop) || (rectOneRight <= rectTwoLeft) ||
		(rectOneTop >= rectTwoBottom) || (rectOneLeft >= rectTwoRight))
		return false;
	else return true;
}

void Game::render() {

	SDL_RenderClear(Middleware::renderer);
	SDL_RenderPresent(Middleware::renderer);
}


void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Middleware::renderer);

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Game::running() {
	return isRunning;
}
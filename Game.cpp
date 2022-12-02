#include "Game.h"
#include <SDL_mixer.h>
#include "Archer.h"
#include "Bird.h"
#include "BirdOne.h"
#include "BirdTwo.h"
#include "Eagle.h"
#include "Dragon.h"
#include "Cloud.h"
#include "Sun.h"

using namespace std;

Game* Game::instance = nullptr;
SDL_Texture* ArcherTexture;
SDL_Texture* BirdOneTexture;
SDL_Texture* BirdTwoTexture;
SDL_Texture* CloudTexture;
SDL_Texture* EagleTexture;
SDL_Texture* DragonTexture;
SDL_Texture* SunTexture;
SDL_Texture* BackgroundTexture;

SDL_Rect backgroundRect = { 0,0,Middleware::SCREEN_WIDTH,Middleware::SCREEN_HEIGHT };

vector<GameObject*> bird_list;
vector<GameObject*> ui_elements_list;

bool key_press = false;

GameObject* archer;

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
			Middleware::renderer = SDL_CreateRenderer(window, -1, 0);
			if (Middleware::renderer) {
				SDL_SetRenderDrawColor(Middleware::renderer, 23, 166, 253, 255);
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
		loadMedia();
		archer = new Archer(ArcherTexture, 0, Middleware::SCREEN_HEIGHT-230);
		GameObject* sun = new Sun(SunTexture, 0, 0);
		ui_elements_list.insert(ui_elements_list.begin(), sun);

	}
}

void Game::setPreviousGameState(string state) {}
string Game::saveGameStateVariables() {

	string state = "<GameState>\n";
	//state += "";
	return state.c_str();
}

void Game::loadMedia() {
	BackgroundTexture = Middleware::LoadTexture("Images/background.jpg");
	ArcherTexture = Middleware::LoadTexture("Images/archer.png");
	BirdTwoTexture = Middleware::LoadTexture("Images/bird_two.png");
	BirdOneTexture = Middleware::LoadTexture("Images/bird_one.png");
	CloudTexture = Middleware::LoadTexture("Images/cloud.png");
	DragonTexture = Middleware::LoadTexture("Images/dragon.png");
	EagleTexture = Middleware::LoadTexture("Images/eagle.png");
	SunTexture = Middleware::LoadTexture("Images/sun.png");
}

void Game::handleEvents() {


	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {

		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (archer->src_rect.x < 720) {
					archer->setState("movingleft");
				}
				break;
			case SDLK_RIGHT:
				if (archer->src_rect.x < 720) {
					archer->setState("movingright");
				}
				break;
			case SDLK_SPACE:
				break;
			case SDLK_b:
				cout << "Pressed B" << endl;
				break;
			}
		}
		else if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				archer->setState("still");
				archer->src_rect.x = 0;
				break;
			case SDLK_RIGHT:
				archer->setState("still");
				archer->src_rect.x = 0;
				break;
			}
		}
	}
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		archer->y_pos--;
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		archer->y_pos++;
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		archer->x_pos--;
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		archer->x_pos++;
	}
	}

void Game ::handleGameChanges() {

	Middleware::nSpeedCount++;

	//--------------------------------animate-----------------------------------------
	if (Middleware::nSpeedCount % 30 == 0) {
		Middleware::animate(bird_list);
	}

	if (Middleware::nSpeedCount % 10 == 0) {
		if (archer->getName() == "archer") {
			if (archer->getState() == "still") {
				if (archer->src_rect.x == 600) {
					archer->src_rect.x = 0;
				}
				else {
					archer->src_rect.x += 120;
				}
			}
			if (archer->getState() == "movingleft" || archer->getState() == "movingright") {
				if (archer->src_rect.x == 2280) {
					archer->src_rect.x = 720;
				}
				else {
					archer->src_rect.x += 120;
				}
			}
		}
	}
	

	//--------------------------------insert-----------------------------------------
	if (Middleware::nSpeedCount % 1500 == 0) {
		int random = rand() % 200;
		GameObject* cloud = new Cloud(CloudTexture, -150, random);
		ui_elements_list.insert(ui_elements_list.begin(), cloud);
	}

	if (Middleware::nSpeedCount % 800 == 0) {
		int select_random = rand() % 3;
		//will fix this later
		int position_random = 100 + rand() % 200;

		if (select_random == 0) {
			GameObject* bird_one = new BirdOne(BirdOneTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), bird_one);
		}
		if (select_random == 1) {
			GameObject* bird_two = new BirdTwo(BirdTwoTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), bird_two);
		}
		if (select_random == 2) {
			GameObject* dragon = new Dragon(DragonTexture, -200, position_random);
			bird_list.insert(bird_list.begin(), dragon);
		}
		if (select_random == 3) {
			GameObject* eagle = new Eagle(EagleTexture, -100, position_random);
			bird_list.insert(bird_list.begin(), eagle);
		}

	}


	//--------------------------------move-----------------------------------------
	Middleware::move(bird_list);
	Middleware::move(ui_elements_list);

	
	//--------------------------------clean-----------------------------------------
	Middleware::clean(bird_list);
	Middleware::clean(ui_elements_list);
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

	SDL_Delay(3);

	SDL_RenderClear(Middleware::renderer);
	SDL_RenderCopy(Middleware::renderer, BackgroundTexture, NULL, &backgroundRect);

	archer->render();
	Middleware::render(ui_elements_list);
	Middleware::render(bird_list);

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
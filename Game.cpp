#include "Game.h"
#include <SDL_mixer.h>
#include "Archer.h"
#include "Bird.h"
#include "GreyBird.h"
#include "RedBird.h"
#include "Eagle.h"
#include "YellowBird.h"
#include "GreyBirdEgg.h"
#include "RedBirdEgg.h"
#include "YellowBirdEgg.h"
#include "EagleBirdEgg.h"
#include "Dragon.h"
#include "Cloud.h"
#include "Sun.h"
#include "Bow.h"

using namespace std;

Game* Game::instance = nullptr;
SDL_Texture* ArcherTexture;
SDL_Texture* GreyBirdTexture;
SDL_Texture* RedBirdTexture;
SDL_Texture* YellowBirdTexture;
SDL_Texture* EagleTexture;

SDL_Texture* GreyEggTexture;
SDL_Texture* RedEggTexture;
SDL_Texture* YellowEggTexture;
SDL_Texture* EagleEggTexture;

SDL_Texture* CloudTexture;
SDL_Texture* DragonTexture;
SDL_Texture* SunTexture;
SDL_Texture* BackgroundTexture;

SDL_Texture* BowTexture;

Mix_Music* gameMusic = NULL;
Mix_Chunk* explosion = NULL;
Mix_Chunk* missileShoot = NULL;
Mix_Chunk* laserShoot = NULL;
Mix_Chunk* enemyShoot = NULL;

double Game::playerX = 0;
double Game::playerY = 0;
GameObject* bow;

SDL_Rect backgroundRect = { 0,0,Middleware::SCREEN_WIDTH,Middleware::SCREEN_HEIGHT };

vector<GameObject*> bird_list;
vector<GameObject*> egg_list;
vector<GameObject*> ui_elements_list;


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

void Game::playGameMusic() {
	Mix_HaltMusic();
	//If there is no music playing
	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(gameMusic, -1);
	else
	{
		if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
		else Mix_PauseMusic();

	}
}

void Game::resetGame() {

	Mix_HaltMusic();
	initializeGameStart();
	Middleware::cleanEntireList(ui_elements_list);
	Middleware::cleanEntireList(bird_list);
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
		loadMedia();
		initializeGameStart();
	}
}

//void Game::updateScore() {
//	TTF_Font* SpaceFont = TTF_OpenFont("Font/SpaceMission-rgyw9.otf", 24);
//	SDL_Rect Missile_rect = { 570,10,100,100 };
//	SDL_Rect Health_rect = { 300,10,100,100 };
//	SDL_Rect Score_rect = { 30,10,100,100 };
//	SDL_Color Color = { 255, 255, 255 ,255 };
//	stringstream ss;
//	string display_missile;
//	ss << missile_limit;
//	ss >> display_missile;
//
//	string missilesLeftMessage = "Missiles Left: " + display_missile;
//	surfaceMessage = TTF_RenderText_Solid(SpaceFont, missilesLeftMessage.c_str(), Color);
//	Missiles_Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
//
//	SDL_QueryTexture(Missiles_Message, NULL, NULL, &Missile_rect.w, &Missile_rect.h);
//
//	stringstream ss2;
//	string display_score;
//	ss2 << score;
//	ss2 >> display_score;
//
//	string displayMessageScore = "Your Score: " + display_score;
//	surfaceMessage = TTF_RenderText_Solid(SpaceFont, displayMessageScore.c_str(), Color);
//	Score_Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
//	SDL_QueryTexture(Score_Message, NULL, NULL, &Score_rect.w, &Score_rect.h);
//
//	if (boss_enemy != nullptr && isEnemyCreated) {
//
//		stringstream ss3;
//		string display_boss_health;
//		ss3 << boss_enemy->count_lives;
//		ss3 >> display_boss_health;
//
//		string displayBossHealth = "Boss Hits Left: " + display_boss_health;
//		surfaceMessage = TTF_RenderText_Solid(SpaceFont, displayBossHealth.c_str(), Color);
//		HealthMessage = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
//
//
//
//		SDL_QueryTexture(HealthMessage, NULL, NULL, &Health_rect.w, &Health_rect.h);
//	}
//
//}

void Game::initializeGameStart() {
	playGameMusic();
	isRunning = true;
	archer = new Archer(ArcherTexture, 0, Middleware::SCREEN_HEIGHT - 230);
	GameObject* sun = new Sun(SunTexture, 0, 0);
	ui_elements_list.insert(ui_elements_list.begin(), sun);

	int generate_random_cloud = rand() % 10;

	for (int i = 0; i <= generate_random_cloud; i++) {
		int random_clouds_x = rand() % Middleware::SCREEN_WIDTH;
		int random_clouds_y = rand() % Middleware::SCREEN_HEIGHT / 2;
		GameObject* cloud = new Cloud(CloudTexture, random_clouds_x, random_clouds_y);
		ui_elements_list.insert(ui_elements_list.begin(), cloud);
	}
}

void Game::setPreviousGameState(string state) {}
string Game::saveGameStateVariables() {

	string state = "<GameState>\n";
	//state += "";
	return state.c_str();
}

void Game::loadMedia() {
	//load the textures
	BackgroundTexture = Middleware::LoadTexture("Images/background.jpg");
	ArcherTexture = Middleware::LoadTexture("Images/archer.png");
	GreyBirdTexture = Middleware::LoadTexture("Images/grey_bird.png");
	YellowBirdTexture = Middleware::LoadTexture("Images/yellow_bird.png");
	RedBirdTexture = Middleware::LoadTexture("Images/red_bird.png");
	CloudTexture = Middleware::LoadTexture("Images/cloud.png");
	DragonTexture = Middleware::LoadTexture("Images/dragon.png");
	EagleTexture = Middleware::LoadTexture("Images/eagle.png");
	SunTexture = Middleware::LoadTexture("Images/sun.png");
	GreyEggTexture = Middleware::LoadTexture("Images/grey_egg.png");
	RedEggTexture = Middleware::LoadTexture("Images/red_egg.png");
	YellowEggTexture = Middleware::LoadTexture("Images/yellow_egg.png");
	EagleEggTexture = Middleware::LoadTexture("Images/.png");
	BowTexture = Middleware::LoadTexture("Images/bow.png");

	//load the music and sound effects
	gameMusic = Mix_LoadMUS("Music/Game_Music.mp3");
	explosion = Mix_LoadWAV("Music/Sound Effects/explosion.wav");
	laserShoot = Mix_LoadWAV("Music/Sound Effects/laserShoot.wav");
	missileShoot = Mix_LoadWAV("Music/Sound Effects/missileShoot.wav");
	enemyShoot = Mix_LoadWAV("Music/Sound Effects/enemyShoot.wav");
}

void Game::handleEvents() {


	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {

		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		if (event.type == SDL_KEYDOWN) {
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
			}
		}
		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				archer->setState("still");
				break;
			case SDLK_RIGHT:
				archer->setState("still");
				break;
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (SDL_BUTTON_LEFT == event.button.button) {
				bow = new Bow(BowTexture,archer->x_pos,archer->y_pos,x,y);
				archer->setState("shoot");
			}
		}
	}
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
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
			if (archer->getState() == "dead") {
				if (archer->src_rect.x == 3600) {
					archer->src_rect.x = 3600;
					//isRunning = false;
				}
				else {
					archer->src_rect.x += 120;
				}
			}
			if (archer->getState() == "shoot") {
				if (archer->src_rect.x == 3000) {
					egg_list.insert(egg_list.begin(), bow);
					archer->setState("still");
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
		//int select_random = 3;

		if (select_random == 0) {
			GameObject* grey_bird = new GreyBird(GreyBirdTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), grey_bird);
		}
		if (select_random == 1) {
			GameObject* yellow_bird = new YellowBird(YellowBirdTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), yellow_bird);
		}
		if (select_random == 2) {
			GameObject* red_bird = new RedBird(RedBirdTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), red_bird);
		}
		if (select_random == 3) {
			GameObject* dragon = new Dragon(DragonTexture, -200, position_random);
			bird_list.insert(bird_list.begin(), dragon);
		}
		if (select_random == 4) {
			GameObject* eagle = new Eagle(EagleTexture, -100, position_random);
			bird_list.insert(bird_list.begin(), eagle);
		}

	}

	if (Middleware::nSpeedCount % 600 == 0)
	{
		for (int i = 0; i < bird_list.size(); i++) {

			if (bird_list.at(i)->getName() == "grey_bird" && bird_list.at(i)->getState() != "die") {
				GameObject* gameObject = bird_list.at(i);
				GameObject* egg = new GreyBirdEgg(GreyEggTexture, gameObject->x_pos+gameObject->getWidth()/2, gameObject->y_pos + gameObject->getHeight() / 2);
				egg_list.insert(egg_list.begin(), egg);
				Mix_PlayChannel(-1, enemyShoot, 0);
			}


			if (bird_list.at(i)->getName() == "yellow_bird" && bird_list.at(i)->getState() != "die") {
				GameObject* gameObject = bird_list.at(i);
				GameObject* egg = new YellowBirdEgg(YellowEggTexture, gameObject->x_pos + gameObject->getWidth() / 2, gameObject->y_pos + gameObject->getHeight() / 2);
				egg_list.insert(egg_list.begin(), egg);
				Mix_PlayChannel(-1, enemyShoot, 0);
			}


			if (bird_list.at(i)->getName() == "red_bird" && bird_list.at(i)->getState() != "die") {
				GameObject* gameObject = bird_list.at(i);
				GameObject* egg = new RedBirdEgg(RedEggTexture, gameObject->x_pos + gameObject->getWidth() / 2, gameObject->y_pos + gameObject->getHeight() / 2);
				egg_list.insert(egg_list.begin(), egg);
				Mix_PlayChannel(-1, enemyShoot, 0);
			}

		}
	}

	//--------------------------------collision detection-----------------------------------------
	for (int b = 0; b < egg_list.size(); b++)
	{

		if (egg_list.at(b)->getName() == "grey_bird_egg" || egg_list.at(b)->getName() == "red_bird_egg" || egg_list.at(b)->getName() == "yellow_bird_egg") {
			GameObject* gameObject = egg_list.at(b);
			if (checkCollision(gameObject, archer)) {
				gameObject->setAliveToFalse();
				archer->setAliveToFalse();
				archer->setState("dead");
			}
		}

		//Collision with enemy with usermissile
		if (egg_list.at(b)->getName() == "bow") {
			GameObject* bowObject = egg_list.at(b);

			for (int n = 0; n < bird_list.size(); n++)
			{
				GameObject* gameObject = bird_list.at(n);
				if (checkCollision(bowObject, gameObject)) {

					if (bird_list.at(n)->getName() == "red_bird" || bird_list.at(n)->getName() == "grey_bird" ||
						bird_list.at(n)->getName() == "yellow_bird") {
						bowObject->setAliveToFalse();
						gameObject->setState("die");
						Mix_PlayChannel(-1, explosion, 0);
					}
				}
			}
		}

	}




	playerX = archer->x_pos;
	playerY = archer->y_pos;


	//--------------------------------move-----------------------------------------
	Middleware::move(bird_list);
	Middleware::move(egg_list);
	Middleware::move(ui_elements_list);

	
	//--------------------------------clean-----------------------------------------
	Middleware::clean(bird_list);
	Middleware::clean(egg_list);
	Middleware::clean(ui_elements_list);
}

bool Game::checkCollision(GameObject* game_object_one, GameObject* game_object_two)
{

	SDL_Rect rectOne = game_object_one->getDstRect();
	SDL_Rect rectTwo = game_object_two->getDstRect();

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

	SDL_Delay(2);

	SDL_RenderClear(Middleware::renderer);
	SDL_RenderCopy(Middleware::renderer, BackgroundTexture, NULL, &backgroundRect);

	archer->render();
	Middleware::render(ui_elements_list);
	Middleware::render(bird_list);
	Middleware::render(egg_list);

	SDL_RenderPresent(Middleware::renderer);
}


void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Middleware::renderer);
	
	SDL_DestroyTexture(ArcherTexture);
	SDL_DestroyTexture(GreyBirdTexture);
	SDL_DestroyTexture(RedBirdTexture);
	SDL_DestroyTexture(YellowBirdTexture);
	SDL_DestroyTexture(EagleTexture);
	SDL_DestroyTexture(GreyEggTexture);
	SDL_DestroyTexture(RedEggTexture);
	SDL_DestroyTexture(YellowEggTexture);
	SDL_DestroyTexture(EagleEggTexture);
	SDL_DestroyTexture(CloudTexture);
	SDL_DestroyTexture(DragonTexture);
	SDL_DestroyTexture(SunTexture);
	SDL_DestroyTexture(BackgroundTexture);


	//Free the music
	Mix_FreeMusic(gameMusic);
	gameMusic = NULL;

	//Free the sound effects
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(enemyShoot);
	Mix_FreeChunk(laserShoot);
	Mix_FreeChunk(missileShoot);


	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Game::running() {
	return isRunning;
}
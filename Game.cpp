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
#include "LevelOne.h"
#include "LevelTwo.h"
#include "Explosion.h"
#include "DragonFire.h"
#include "HealthBar.h"
#include "FileManager.h"
#include <sstream>
#include <iostream>


using namespace std;

Game* Game::game_instance = nullptr;

Game::Game() {
	window = nullptr;
	isRunning = false;
	game_score = 0;
	bow_count = 10;
	prev_score = 0;
	prev_bows = 0;
	isLevelOneBossCreated = false;
	isLevelTwoBossCreated = false;
	level_number = 1;
	backgroundRect = { 0,0,Middleware::SCREEN_WIDTH,Middleware::SCREEN_HEIGHT };
	Bow_Count_Rect = {0,0,0,0};
	Score_Rect = { 0,0,0,0 };
	Level_Number_Rect = { 0,0,0,0 };
	lives_Rect = { 0,0,0,0 };
	health_Rect = { 0,0,0,0 };
	archer = nullptr;
	bow = nullptr;
}

Game::~Game() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Middleware::renderer);
	TTF_Quit();
	SDL_Quit();
}

void Game::startLevelTwo() {
	Texture::getInstance()->setBackgroundTexture(Texture::getInstance()->getBackground_Level_Two_Texture());
	level_number = 2;
	Middleware::cleanEntireList(bird_list);
	Middleware::cleanEntireList(egg_list);
	Middleware::cleanEntireList(explosion_list);
	archer = Archer::getInstance();
	archer->setGroundHeight(Middleware::LEVEL_TWO_GROUND_HEIGHT);
}


Game* Game::getInstance() {

	if (game_instance == nullptr) {
		game_instance = new Game();
	}
	return game_instance;

}

void Game::playGameMusic() {
	Mix_HaltMusic();
	//If there is no music playing
	if (Mix_PlayingMusic() == 0) Mix_PlayMusic(Music::getMusicInstance()->getGameMusic(), -1);
	else
	{
		if (Mix_PausedMusic() == 1) Mix_ResumeMusic();
		else Mix_PauseMusic();

	}
}

void Game::resetGame(string menu_selection) {
	FileManager::getInstance()->makeFileWithStates(bird_list, egg_list);
	Mix_HaltMusic();
	Middleware::cleanEntireList(ui_elements_list);
	Middleware::cleanEntireList(bird_list);
	Middleware::cleanEntireList(egg_list);
	Middleware::cleanEntireList(explosion_list);
	initializeGameStart(menu_selection);
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
		loadMedia();
		GameObject* sun = new Sun(Texture::getInstance()->getSunTexture(), 0, 0);
		ui_elements_list.insert(ui_elements_list.begin(), sun);

		int generate_random_cloud = rand() % 10;
		for (int i = 0; i <= generate_random_cloud; i++) {
			int random_clouds_x = rand() % Middleware::SCREEN_WIDTH;
			int random_clouds_y = rand() % Middleware::SCREEN_HEIGHT / 2;
			GameObject* cloud = new Cloud(Texture::getInstance()->getCloudTexture(), random_clouds_x, random_clouds_y);
			ui_elements_list.insert(ui_elements_list.begin(), cloud);
		}

		archer = Archer::getInstance();
		updateScore();
		GameObject* health_bar = new HealthBar(Texture::getInstance()->getHealthBarTexture(), Middleware::SCREEN_WIDTH - 200, 50);
		ui_elements_list.insert(ui_elements_list.begin(), health_bar);
	}
}

void Game::initializeGameStart(string menu_selection) {
	playGameMusic();
	isRunning = true;
	if (menu_selection == "continue") FileManager::getInstance()->readFileAndContinue(bird_list, egg_list, ui_elements_list);
	else if (menu_selection == "new") {
		game_score = 0;
		bow_count = 10;
		prev_score = 0;
		prev_bows = 0;
		isLevelOneBossCreated = false;
		isLevelTwoBossCreated = false;
		level_number = 1;
		Texture::getInstance()->setBackgroundTexture(Texture::getInstance()->getBackground_Level_One_Texture());
		archer = Archer::getInstance();
		archer->setLives(5);
		archer->setState("still");
	}

	GameObject* sun = new Sun(Texture::getInstance()->getSunTexture(), 0, 0);
	ui_elements_list.insert(ui_elements_list.begin(), sun);
	GameObject* health_bar = new HealthBar(Texture::getInstance()->getHealthBarTexture(), Middleware::SCREEN_WIDTH - 200, 50);
	ui_elements_list.insert(ui_elements_list.begin(), health_bar);
	updateScore();
}


void Game::initializePreviousGameState(string state) {
	istringstream f(state);
	string line;
	int counter = 0;
	while (getline(f, line)) {
		if (counter == 0) game_score = stoi(line);
		if (counter == 1) bow_count = stoi(line);
		if (counter == 2) prev_score = stoi(line);
		if (counter == 3) prev_bows = stoi(line);
		if (counter == 4) level_number = stoi(line);
		if (counter == 5) {
			if (line == "1") isLevelOneBossCreated = true;
			else isLevelOneBossCreated = false;
		}
		if (counter == 6) {
			if (line == "1") isLevelTwoBossCreated = true;
			else isLevelTwoBossCreated = false;
		}
		counter++;
	}
}

string Game::saveGameStateVariables() {


	string state = "<GameState>\n";
	state += Middleware::intToString(game_score) + "\n";
	state += Middleware::intToString(bow_count) + "\n";
	state += Middleware::intToString(prev_score) + "\n";
	state += Middleware::intToString(prev_bows) + "\n";
	state += Middleware::intToString(level_number) + "\n";
	state += Middleware::boolToString(isLevelOneBossCreated) + "\n";
	state += Middleware::boolToString(isLevelTwoBossCreated) + "\n";
	return state.c_str();
}


void Game::loadMedia() {
	//load the textures
	Texture::getInstance();
}

SDL_Point Game::getSize(SDL_Texture* texture) {
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	return size;
}

void Game::updateScore() {
	TTF_Font* SpaceFont = TTF_OpenFont("Fonts/SpaceMission-rgyw9.otf", 24);
	SDL_Color Color = { 255, 255, 255 ,255 };

	string bows_left = "Bows Left: " + Middleware::intToString(bow_count);
	SDL_Surface* BowsLeftSurface = TTF_RenderText_Solid(SpaceFont, bows_left.c_str(), Color);
	Texture::getInstance()->setBowsLeftTexture(SDL_CreateTextureFromSurface(Middleware::renderer, BowsLeftSurface));
	SDL_Point BowTitlePoint = getSize(Texture::getInstance()->getBowsLeftTexture());
	Bow_Count_Rect = { Middleware::SCREEN_WIDTH - BowTitlePoint.x - 30,10,BowTitlePoint.x,BowTitlePoint.y };

	string score = "Score: " + Middleware::intToString(game_score);
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(SpaceFont, score.c_str(), Color);
	Texture::getInstance()->setscoreTexture(SDL_CreateTextureFromSurface(Middleware::renderer, scoreSurface));
	SDL_Point ScoreTitlePoint = getSize(Texture::getInstance()->getscoreTexture());
	Score_Rect = { Middleware::SCREEN_WIDTH - ScoreTitlePoint.x - BowTitlePoint.x - 60,10,ScoreTitlePoint.x,ScoreTitlePoint.y };

	string level = "Level #" + Middleware::intToString(level_number);
	SDL_Surface* levelSurface = TTF_RenderText_Solid(SpaceFont, level.c_str(), Color);
	Texture::getInstance()->setLevelNumberTexture(SDL_CreateTextureFromSurface(Middleware::renderer, levelSurface));
	SDL_Point LevelTitlePoint = getSize(Texture::getInstance()->getLevelNumberTexture());
	Level_Number_Rect = { Middleware::SCREEN_WIDTH - LevelTitlePoint.x - ScoreTitlePoint.x - BowTitlePoint.x - 90,10,LevelTitlePoint.x,LevelTitlePoint.y };


	if (isLevelOneBossCreated || isLevelTwoBossCreated) {
		for (int i = 0; i < bird_list.size(); i++)
		{
			if (bird_list.at(i)->getName() == "eagle" || bird_list.at(i)->getName() == "dragon") {
				string Lives = bird_list.at(i)->getName() + " Lives: " + Middleware::intToString(bird_list.at(i)->getLives());
				SDL_Surface* livesSurface = TTF_RenderText_Solid(SpaceFont, Lives.c_str(), Color);

				Texture::getInstance()->setlivesTexture(SDL_CreateTextureFromSurface(Middleware::renderer, livesSurface));
				SDL_Point livesTitlePoint = getSize(Texture::getInstance()->getlivesTexture());
				lives_Rect = { Middleware::SCREEN_WIDTH - livesTitlePoint.x - LevelTitlePoint.x - ScoreTitlePoint.x - BowTitlePoint.x - 120,10,livesTitlePoint.x,livesTitlePoint.y };

			}
		}

	}
	for (int i = 0; i < ui_elements_list.size(); i++)
	{
		if (ui_elements_list.at(i)->getName() == "health_bar") {
			ui_elements_list.at(i)->setState(Middleware::intToString(archer->getLives()));
		}
	}

}

void Game::update() {
	Middleware::nSpeedCount++;
	archer->move();
	//--------------------------------animate-----------------------------------------
	if (Middleware::nSpeedCount % 30 == 0) {
		Middleware::animate(bird_list);
		Middleware::animate(egg_list);
	}


	if (Middleware::nSpeedCount % 10 == 0) {
		bool animation_complete = archer->animate();
		if (animation_complete && (archer->getState() == "shootright" || archer->getState() == "shootleft" || archer->getState() == "shootlowleft" || archer->getState() == "shootlowright")) {
			egg_list.insert(egg_list.begin(), bow);
			archer->setState("still");
		}
	}




	if (Middleware::nSpeedCount % 600 == 0) insertEggs();
	//--------------------------------------------------collision detection-----------------------------------------
	detectCollisions();


	//Increase missile limit with time
	if (Middleware::nSpeedCount % 500 == 0) {
		if (bow_count < 10) {
			bow_count++;
			updateScore();
		}
	}



	//--------------------------------move-----------------------------------------
	Middleware::move(bird_list);
	Middleware::move(egg_list);
	Middleware::move(ui_elements_list);
	Middleware::move(explosion_list);

	//--------------------------------clean-----------------------------------------
	Middleware::clean(bird_list);
	Middleware::clean(egg_list);
	Middleware::clean(ui_elements_list);
	Middleware::clean(explosion_list);
}

void Game::handleEvents() {


	SDL_Event event;

	while (SDL_PollEvent(&event) != 0) {

		if (event.type == SDL_QUIT) {
			isRunning = false;
		}
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
				archer->setState("still");
			}
		}
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_w) {
				if (archer->getSrcRect().x < 36 * archer->getWidth()) {
					archer->setState("jump");
					Mix_PlayChannel(-1, Music::getMusicInstance()->getJumpSound(), 0);
				}
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (SDL_BUTTON_LEFT == event.button.button) {
				if (bow_count > 0) {
					if (archer->getState() == "movingright") bow = new Bow(Texture::getInstance()->getBowTexture(), archer->getX() + archer->getWidth() / 2, archer->getY() + archer->getHeight() / 4, x, y);
					else bow = new Bow(Texture::getInstance()->getBowTexture(), archer->getX() + archer->getWidth() / 4, archer->getY() + archer->getHeight() / 4, x, y);
					bow_count--;
					updateScore();
					if (bow->getAngleInDegrees() <= -194 && bow->getAngleInDegrees() >= -265) {
						archer->setState("shootright");
					}
					else if (bow->getAngleInDegrees() <= -170 && bow->getAngleInDegrees() >= -193) {
						archer->setState("shootlowright");
					}
					else if (bow->getAngleInDegrees() <= -266 && bow->getAngleInDegrees() >= -350) {
						archer->setState("shootleft");
					}
					else archer->setState("shootlowleft");
				}
				Mix_PlayChannel(-1, Music::getMusicInstance()->getBowSound(), 0);
			}
		}
	}
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_A]) {
		if (archer->getSrcRect().x < 6 * archer->getWidth() || archer->getSrcRect().x > 19 * archer->getWidth()) {
			archer->setState("movingleft");
		}
	}
	if (currentKeyStates[SDL_SCANCODE_D]) {
		if (archer->getSrcRect().x < 6 * archer->getWidth() || archer->getSrcRect().x > 19 * archer->getWidth()) {
			archer->setState("movingright");
		}
	}
}

int Game::handleLevelTwoChanges() {
	LevelTwo::getInstance()->handleChanges(ui_elements_list, bird_list, game_score, isLevelOneBossCreated);
	return level_number;
}

int Game ::handleLevelOneChanges() {
	LevelOne::getInstance()->handleChanges(ui_elements_list, bird_list, game_score, isLevelTwoBossCreated);
	return level_number;
}

void Game::detectCollisions() {
	for (int b = 0; b < egg_list.size(); b++)
	{

		if (egg_list.at(b)->getName() == "grey_bird_egg" || egg_list.at(b)->getName() == "red_bird_egg" || egg_list.at(b)->getName() == "yellow_bird_egg" || egg_list.at(b)->getName() == "eagle_bird_egg" || egg_list.at(b)->getName() == "dragon_fire") {
			GameObject* gameObject = egg_list.at(b);
			if (checkCollision(gameObject, archer)) {
				if (gameObject->getState() != "dead") {
					if (archer->getLives() == 1) {
						archer->setAliveToFalse();
						isRunning = false;
					}
					else {
						if (gameObject->getName() != "dragon_fire") gameObject->setSrcRectX(32);
						archer->setState("dead");
						gameObject->setState("dead");
						archer->reduceLives();
						updateScore();
						Mix_PlayChannel(-1, Music::getMusicInstance()->getArcherHitSound(), 0);
					}
				}
				updateScore();
			}
		}

		//Collision of bird with bow
		if (egg_list.at(b)->getName() == "bow") {
			GameObject* bowObject = egg_list.at(b);

			for (int n = 0; n < bird_list.size(); n++)
			{
				GameObject* gameObject = bird_list.at(n);
				if (checkCollision(bowObject, gameObject)) {

					if (bird_list.at(n)->getName() == "red_bird" || bird_list.at(n)->getName() == "grey_bird" ||
						bird_list.at(n)->getName() == "yellow_bird") {
						Middleware::createExplosion(gameObject, Texture::getInstance()->getExplosionTexture(), explosion_list, Music::getMusicInstance()->getBird1Hit());
						bowObject->setAliveToFalse();
						gameObject->setState("die");
						game_score += 100;
						updateScore();
					}

					if (bird_list.at(n)->getName() == "eagle") {
						Middleware::createExplosion(gameObject, Texture::getInstance()->getExplosionTexture(), explosion_list, Music::getMusicInstance()->getEagleHit());
						bowObject->setAliveToFalse();
						if (gameObject->getLives() == 0) {
							gameObject->setAliveToFalse();
							level_number = 2;
						}
						else {
							gameObject->reduceLives();
							game_score += 300;
						}
						updateScore();
					}

					if (bird_list.at(n)->getName() == "dragon") {
						Middleware::createExplosion(gameObject, Texture::getInstance()->getExplosion2Texture(), explosion_list, Music::getMusicInstance()->getEagleHit());
						bowObject->setAliveToFalse();
						if (gameObject->getLives() == 0) {
							gameObject->setAliveToFalse();
							level_number = 2;
							isRunning = false;
						}
						else {
							gameObject->reduceLives();
							game_score += 500;
						}
						updateScore();
					}
				}
			}
		}
	}
}
void Game::insertEggs() {
	for (int i = 0; i < bird_list.size(); i++) {

		GameObject* gameObject = bird_list.at(i);

		if (gameObject->getName() == "grey_bird" && gameObject->getState() != "die") {
			GameObject* egg = new GreyBirdEgg(Texture::getInstance()->getGreyEggTexture(), gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, Music::getMusicInstance()->getEggShoot(), 0);
		}


		if (gameObject->getName() == "yellow_bird" && gameObject->getState() != "die") {
			GameObject* egg = new YellowBirdEgg(Texture::getInstance()->getYellowEggTexture(), gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, Music::getMusicInstance()->getEggShoot(), 0);
		}


		if (gameObject->getName() == "eagle" && gameObject->getState() != "die") {
			GameObject* egg = new EagleBirdEgg(Texture::getInstance()->getEagleEggTexture(), gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, Music::getMusicInstance()->getEggShoot(), 0);
		}

		if (gameObject->getName() == "red_bird" && gameObject->getState() != "die") {
			GameObject* egg = new RedBirdEgg(Texture::getInstance()->getRedEggTexture(), gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, Music::getMusicInstance()->getEggShoot(), 0);
		}

		if (gameObject->getName() == "dragon" && gameObject->getState() != "die") {

			double dragon_fire_xpos;
			if (gameObject->getState() == "movingright") dragon_fire_xpos = gameObject->getX() + gameObject->getWidth() - 30;
			else dragon_fire_xpos = gameObject->getX() + 10;

			GameObject* fire = new DragonFire(Texture::getInstance()->getDragonFireTexture(), dragon_fire_xpos, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), fire);
			Mix_PlayChannel(-1, Music::getMusicInstance()->getDragonFire(), 0);
		}
	}
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

	SDL_RenderClear(Middleware::renderer);
	SDL_RenderCopy(Middleware::renderer, Texture::getInstance()->getBackgroundTexture(), NULL, &backgroundRect);

	archer->render();
	Middleware::render(ui_elements_list);
	Middleware::render(bird_list);
	Middleware::render(egg_list);
	Middleware::render(explosion_list);

	SDL_RenderCopy(Middleware::renderer, Texture::getInstance()->getscoreTexture(), NULL, &Score_Rect);
	SDL_RenderCopy(Middleware::renderer, Texture::getInstance()->getBowsLeftTexture(), NULL, &Bow_Count_Rect);
	SDL_RenderCopy(Middleware::renderer, Texture::getInstance()->getLevelNumberTexture(), NULL, &Level_Number_Rect);

	for (int i = 0; i < bird_list.size(); i++)
	{
		if ((bird_list.at(i)->getName() == "eagle" || bird_list.at(i)->getName() == "dragon") && bird_list.at(i)->getAlive()==true) {
			SDL_RenderCopy(Middleware::renderer, Texture::getInstance()->getlivesTexture(), NULL, &lives_Rect);
		}
	}
	SDL_RenderPresent(Middleware::renderer);
}


bool Game::running() {
	return isRunning;
}

int Game::getLevelNumber() {
	return level_number;
}

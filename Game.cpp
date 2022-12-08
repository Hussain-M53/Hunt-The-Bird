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
#include "Explosion.h"
#include "DragonFire.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

Game* Game::instance = nullptr;
SDL_Texture* ArcherTexture;
SDL_Texture* GreyBirdTexture;
SDL_Texture* RedBirdTexture;
SDL_Texture* YellowBirdTexture;
SDL_Texture* EagleTexture;
SDL_Texture* ExplosionTexture;

SDL_Texture* GreyEggTexture;
SDL_Texture* RedEggTexture;
SDL_Texture* YellowEggTexture;
SDL_Texture* EagleEggTexture;
SDL_Texture* DragonFireTexture;

SDL_Texture* CloudTexture;
SDL_Texture* DragonTexture;
SDL_Texture* SunTexture;
SDL_Texture* BackgroundTexture;

SDL_Texture* BowTexture;
SDL_Texture* scoreTexture;
SDL_Texture* BowsLeftTexture;
SDL_Texture* LevelNumberTexture;
SDL_Texture* Background_Level_Two_Texture;
SDL_Texture* Background_Level_One_Texture;

SDL_Rect Bow_Count_Rect, Score_Rect, Level_Number_Rect;

Mix_Music* gameMusic = NULL;
Mix_Chunk* explosion = NULL;
Mix_Chunk* dragonFire = NULL;
Mix_Chunk* laserShoot = NULL;
Mix_Chunk* enemyShoot = NULL;
Mix_Chunk* BirdChirp = NULL;

double Game::playerX = 0;
double Game::playerY = 0;
GameObject* bow;

SDL_Rect backgroundRect = { 0,0,Middleware::SCREEN_WIDTH,Middleware::SCREEN_HEIGHT };

vector<GameObject*> bird_list;
vector<GameObject*> egg_list;
vector<GameObject*> ui_elements_list;
vector<GameObject*> explosion_list;


GameObject* archer;

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
}

Game::~Game() {

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
	SDL_DestroyTexture(Background_Level_One_Texture);
	SDL_DestroyTexture(Background_Level_Two_Texture);
	SDL_DestroyTexture(BackgroundTexture);
	SDL_DestroyTexture(ExplosionTexture);


	//Free the music
	Mix_FreeMusic(gameMusic);
	gameMusic = NULL;

	//Free the sound effects
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(enemyShoot);
	Mix_FreeChunk(laserShoot);
	Mix_FreeChunk(dragonFire);

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void Game::startLevelTwo() {
	BackgroundTexture = Background_Level_Two_Texture;
	level_number = 2;
	archer = new Archer(ArcherTexture, 0, Middleware::LEVEL_TWO_GROUND_HEIGHT);
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

void Game::resetGame(string menu_selection) {
	saveStatesinFile();
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
}

void Game::initializeGameStart(string menu_selection) {
	playGameMusic();
	isRunning = true;
	archer = new Archer(ArcherTexture, 0, Middleware::LEVEL_ONE_GROUND_HEIGHT);
	if (menu_selection == "continue") getGamePreviousStates();
	if (menu_selection == "new") {
		game_score = 0;
		bow_count = 10;
		prev_score = 0;
		prev_bows = 0;
		isLevelOneBossCreated = false;
		isLevelTwoBossCreated = false;
		level_number = 1;
		BackgroundTexture = Background_Level_One_Texture;
	}
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


void Game::getGamePreviousStates() {
	string myText;
	string Tag;
	string state;

	ifstream readFile("Game State/game_state.txt");

	while (getline(readFile, myText)) {

		// A game Tag is found
		if ((myText.find('<')) != string::npos && (myText.find('>')) != string::npos) {
			//Player
			cout << Tag << endl;
			cout << state << endl;
			if (Tag == "<Archer>") {
				archer->setPreviousGameState(state);
			}
			//Enemies
			if (Tag == "<GreyBird>") {
				GameObject* gameObject = new GreyBird(GreyBirdTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<YellowBird>") {
				GameObject* gameObject = new YellowBird(YellowBirdTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<RedBird>") {
				GameObject* gameObject = new RedBird(RedBirdTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<Dragon>") {
				GameObject* gameObject = new Dragon(DragonTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<Eagle>") {
				GameObject* gameObject = new Eagle(EagleTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			//Eggs and Fire
			if (Tag == "<GreyBirdEgg>") {
				GameObject* gameObject = new GreyBirdEgg(GreyEggTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<YellowBirdEgg>") {
				GameObject* gameObject = new YellowBirdEgg(YellowEggTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<RedBirdEgg>") {
				GameObject* gameObject = new RedBirdEgg(RedEggTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<EagleBirdEgg>") {
				GameObject* gameObject = new EagleBirdEgg(EagleEggTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<DragonFire>") {
				GameObject* gameObject = new RedBirdEgg(DragonFireTexture, 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<GameState>") {
				initializePreviousGameState(state);
			}

			Tag = myText;
			state = "";
			continue;
		}
		state += myText + "\n";
	}
}



void Game::saveStatesinFile() {

	//Open File
	ofstream file;
	file.open("Game State/game_state.txt");

	//save Player State
	if (archer != nullptr) {
		string getPlayerState = archer->saveState();
		file << getPlayerState;
	}

	//save List States
	file << Middleware::getListStates(bird_list);
	file << Middleware::getListStates(egg_list);

	// save Game States
	file << saveGameStateVariables();

	//add a closing Tag
	file << "<>";
	file.close();
	//Close File
}



void Game::loadMedia() {
	//load the textures
	Background_Level_One_Texture = Middleware::LoadTexture("Images/background.jpg");
	Background_Level_Two_Texture = Middleware::LoadTexture("Images/background_level_two.jpg");
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
	EagleEggTexture = Middleware::LoadTexture("Images/eagle_egg.png");
	BowTexture = Middleware::LoadTexture("Images/bow.png");
	ExplosionTexture = Middleware::LoadTexture("Images/feathers.png");
	DragonFireTexture = Middleware::LoadTexture("Images/dragon_fire.png");
	BackgroundTexture = Background_Level_One_Texture;

	//load the music and sound effects
	gameMusic = Mix_LoadMUS("Music/Game_Music.mp3");
	explosion = Mix_LoadWAV("Music/Sound Effects/explosion.wav");
	//bowShoot = Mix_LoadWAV("Music/Sound Effects/laserShoot.wav");
	dragonFire = Mix_LoadWAV("Music/Sound Effects/dragonFire.wav");
	enemyShoot = Mix_LoadWAV("Music/Sound Effects/laserShoot.wav");
	BirdChirp = Mix_LoadWAV("Music/Sound Effects/birdChirp.mp3");
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
	BowsLeftTexture = SDL_CreateTextureFromSurface(Middleware::renderer, BowsLeftSurface);
	SDL_Point BowTitlePoint = getSize(BowsLeftTexture);
	Bow_Count_Rect = { Middleware::SCREEN_WIDTH- BowTitlePoint.x - 30,10,BowTitlePoint.x,BowTitlePoint.y };

	string score = "Score: " + Middleware::intToString(game_score);
	SDL_Surface* scoreSurface = TTF_RenderText_Solid(SpaceFont, score.c_str(), Color);
	scoreTexture = SDL_CreateTextureFromSurface(Middleware::renderer, scoreSurface);
	SDL_Point ScoreTitlePoint = getSize(scoreTexture);
	Score_Rect = { Middleware::SCREEN_WIDTH - ScoreTitlePoint.x - BowTitlePoint.x - 60,10,ScoreTitlePoint.x,ScoreTitlePoint.y };

	string level = "Level #" + Middleware::intToString(level_number);
	SDL_Surface* levelSurface = TTF_RenderText_Solid(SpaceFont, level.c_str(), Color);
	LevelNumberTexture = SDL_CreateTextureFromSurface(Middleware::renderer, levelSurface);
	SDL_Point LevelTitlePoint = getSize(LevelNumberTexture);
	Level_Number_Rect = { Middleware::SCREEN_WIDTH - LevelTitlePoint.x - ScoreTitlePoint.x - BowTitlePoint.x - 90,10,LevelTitlePoint.x,LevelTitlePoint.y };


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

	//-------------------------------------------------updatescore+playerValues---------------------------------------
	playerX = archer->getX();
	playerY = archer->getY();
	if (prev_score != game_score || prev_bows != bow_count) {
		updateScore();
	}
	prev_score = game_score;
	prev_bows = bow_count;

	//Increase missile limit with time
	if (Middleware::nSpeedCount % 500 == 0) {
		if (bow_count < 10) {
			bow_count++;
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
				if (archer->src_rect.x < 36 * archer->getWidth()) {
					archer->setState("jump");
				}
			}
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if (SDL_BUTTON_LEFT == event.button.button) {
				if (bow_count > 0) {
					if (archer->getState() == "movingright") bow = new Bow(BowTexture, archer->getX() + archer->getWidth() / 2, archer->getY() + archer->getHeight() / 4, x, y);
					else bow = new Bow(BowTexture, archer->getX() + archer->getWidth() / 4, archer->getY() + archer->getHeight() / 4, x, y);
					bow_count--;
					cout << bow->getAngleInDegrees() << endl;
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
			}
		}
	}
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_A]) {
		if (archer->src_rect.x < 6 * archer->getWidth() || archer->src_rect.x > 19 * archer->getWidth()) {
			archer->setState("movingleft");
		}
	}
	if (currentKeyStates[SDL_SCANCODE_D]) {
		if (archer->src_rect.x < 6 * archer->getWidth() || archer->src_rect.x > 19 * archer->getWidth()) {
			archer->setState("movingright");
		}
	}
	}

int Game::handleLevelTwoChanges() {

	//--------------------------------insert-----------------------------------------
	if (Middleware::nSpeedCount % 1500 == 0) {
		int random = rand() % 200;
		GameObject* cloud = new Cloud(CloudTexture, -150, random);
		ui_elements_list.insert(ui_elements_list.begin(), cloud);
	}

	if (Middleware::nSpeedCount % 800 == 0 && game_score < Middleware::LEVEL_TWO_BOSS_SCORE) {
		int select_random = rand() % 1;
		int position_random = 100 + rand() % 200;

		if (select_random == 0) {
			GameObject* red_bird = new RedBird(RedBirdTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), red_bird);
		}

	}
	else if (game_score >= Middleware::LEVEL_TWO_BOSS_SCORE && isLevelTwoBossCreated == false) {
		GameObject* dragon = new Dragon(DragonTexture, -200, 0);
		bird_list.insert(bird_list.begin(), dragon);
		isLevelTwoBossCreated = true;
	}

	return level_number;
}

int Game ::handleLevelOneChanges() {


	//--------------------------------insert-----------------------------------------
	if (Middleware::nSpeedCount % 1500 == 0) {
		int random = rand() % 200;
		GameObject* cloud = new Cloud(CloudTexture, -150, random);
		ui_elements_list.insert(ui_elements_list.begin(), cloud);
	}

	if (Middleware::nSpeedCount % 800 == 0 && game_score < Middleware::LEVEL_ONE_BOSS_SCORE) {
		int select_random = rand() % 2;
		int position_random = 100 + rand() % 200;

		if (select_random == 0) {
			GameObject* grey_bird = new GreyBird(GreyBirdTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), grey_bird);
		}
		if (select_random == 1) {
			GameObject* yellow_bird = new YellowBird(YellowBirdTexture, -64, position_random);
			bird_list.insert(bird_list.begin(), yellow_bird);
		}
		Mix_PlayChannel(-1, BirdChirp, 0);

	}
	else if (game_score>=Middleware::LEVEL_ONE_BOSS_SCORE && isLevelOneBossCreated ==false) {
		int position_random = 100 + rand() % 200;
		GameObject* eagle = new Eagle(EagleTexture, -100, position_random);
		bird_list.insert(bird_list.begin(), eagle);
		isLevelOneBossCreated = true;
	}
	return level_number;
}

void Game::detectCollisions() {
	for (int b = 0; b < egg_list.size(); b++)
	{

		if (egg_list.at(b)->getName() == "grey_bird_egg" || egg_list.at(b)->getName() == "red_bird_egg" || egg_list.at(b)->getName() == "yellow_bird_egg" || egg_list.at(b)->getName() == "eagle_bird_egg") {
			GameObject* gameObject = egg_list.at(b);
			if (checkCollision(gameObject, archer)) {
				gameObject->src_rect.x = 32;
				//gameObject->setAliveToFalse();
				archer->setAliveToFalse();
				archer->setState("dead");
			}
		}

		//Collision with bird with bow
		if (egg_list.at(b)->getName() == "bow") {
			GameObject* bowObject = egg_list.at(b);

			for (int n = 0; n < bird_list.size(); n++)
			{
				GameObject* gameObject = bird_list.at(n);
				if (checkCollision(bowObject, gameObject)) {

					if (bird_list.at(n)->getName() == "red_bird" || bird_list.at(n)->getName() == "grey_bird" ||
						bird_list.at(n)->getName() == "yellow_bird") {
						Middleware::createExplosion(gameObject, ExplosionTexture, explosion_list, explosion);
						bowObject->setAliveToFalse();
						gameObject->setState("die");
						game_score += 100;
					}

					if (bird_list.at(n)->getName() == "eagle") {
						Middleware::createExplosion(gameObject, ExplosionTexture, explosion_list, explosion);
						bowObject->setAliveToFalse();
						if (gameObject->getLives() == 0) {
							gameObject->setAliveToFalse();
							level_number = 2;
						}
						gameObject->reduceLives();
						game_score += 300;
					}

					if (bird_list.at(n)->getName() == "dragon") {
						Middleware::createExplosion(gameObject, ExplosionTexture, explosion_list, explosion);
						bowObject->setAliveToFalse();
						if (gameObject->getLives() == 0) {
							gameObject->setAliveToFalse();
							level_number = 2;
							isRunning = false;
						}
						gameObject->reduceLives();
						game_score += 500;
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
			GameObject* egg = new GreyBirdEgg(GreyEggTexture, gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, enemyShoot, 0);
		}


		if (gameObject->getName() == "yellow_bird" && gameObject->getState() != "die") {
			GameObject* egg = new YellowBirdEgg(YellowEggTexture, gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, enemyShoot, 0);
		}


		if (gameObject->getName() == "eagle" && gameObject->getState() != "die") {
			GameObject* egg = new EagleBirdEgg(EagleEggTexture, gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, enemyShoot, 0);
		}

		if (gameObject->getName() == "red_bird" && gameObject->getState() != "die") {
			GameObject* egg = new RedBirdEgg(RedEggTexture, gameObject->getX() + gameObject->getWidth() / 2, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), egg);
			Mix_PlayChannel(-1, enemyShoot, 0);
		}

		if (gameObject->getName() == "dragon" && gameObject->getState() != "die") {

			double dragon_fire_xpos;
			if (gameObject->getState() == "movingright") dragon_fire_xpos = gameObject->getX() + 10;
			else dragon_fire_xpos = gameObject->getX() + gameObject->getWidth() - 10;

			GameObject* fire = new DragonFire(DragonFireTexture, dragon_fire_xpos, gameObject->getY() + gameObject->getHeight() / 2);
			egg_list.insert(egg_list.begin(), fire);
			Mix_PlayChannel(-1, dragonFire, 0);
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

	SDL_Delay(2);
	SDL_RenderClear(Middleware::renderer);
	SDL_RenderCopy(Middleware::renderer, BackgroundTexture, NULL, &backgroundRect);

	archer->render();
	Middleware::render(ui_elements_list);
	Middleware::render(bird_list);
	Middleware::render(egg_list);
	Middleware::render(explosion_list);

	SDL_RenderCopy(Middleware::renderer, scoreTexture, NULL, &Score_Rect);
	SDL_RenderCopy(Middleware::renderer, BowsLeftTexture, NULL, &Bow_Count_Rect);
	SDL_RenderCopy(Middleware::renderer, LevelNumberTexture, NULL, &Level_Number_Rect);
	SDL_RenderPresent(Middleware::renderer);
}


bool Game::running() {
	return isRunning;
}

int Game::getLevelNumber() {
	return level_number;
}
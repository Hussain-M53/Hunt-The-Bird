#include "LevelOne.h"
#include "Cloud.h"
#include "GreyBird.h"
#include "YellowBird.h"
#include "Eagle.h"
#include "SDL.h"
#include "Music.h"
#include "Texture.h"


LevelOne* LevelOne::level_one_instance = nullptr;

LevelOne::LevelOne() {}
LevelOne::~LevelOne() {}

LevelOne* LevelOne::getInstance() {

	if (level_one_instance == nullptr) {
		level_one_instance = new LevelOne();
	}
	return level_one_instance;
}

void LevelOne::handleChanges(vector<GameObject*>& ui_elements_list, vector<GameObject*>& bird_list, int& game_score, bool& enemyCreated) {

	if (Middleware::nSpeedCount % 1500 == 0) {
		int random = rand() % 200;
		GameObject* cloud = new Cloud(Texture::getInstance()->getCloudTexture(), -150, random);
		ui_elements_list.insert(ui_elements_list.begin(), cloud);
	}

	if (Middleware::nSpeedCount % 800 == 0 && game_score < Middleware::LEVEL_ONE_BOSS_SCORE) {
		int select_random = rand() % 2;
		int position_random = 100 + rand() % 200;

		if (select_random == 0) {
			GameObject* grey_bird = new GreyBird(Texture::getInstance()->getGreyBirdTexture(), -64, position_random);
			bird_list.insert(bird_list.begin(), grey_bird);
		}
		if (select_random == 1) {
			GameObject* yellow_bird = new YellowBird(Texture::getInstance()->getYellowBirdTexture(), -64, position_random);
			bird_list.insert(bird_list.begin(), yellow_bird);
		}
		Mix_PlayChannel(-1, Music::getMusicInstance()->getBirdChirp(), 0);

	}
	else if (game_score >= Middleware::LEVEL_ONE_BOSS_SCORE && enemyCreated == false) {
		int position_random = 100 + rand() % 200;
		GameObject* eagle = new Eagle(Texture::getInstance()->getEagleTexture(), -100, position_random);
		bird_list.insert(bird_list.begin(), eagle);
		enemyCreated = true;
	}
}
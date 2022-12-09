#include "Cloud.h"
#include "GreyBird.h"
#include "YellowBird.h"
#include "Eagle.h"
#include "SDL.h"
#include "Music.h"
#include "Texture.h"

class LevelOne {
public:
	LevelOne(){}
	~LevelOne(){}
	void handleChanges(vector<GameObject*>& ui_elements_list, vector<GameObject*>& bird_list, int& game_score, bool& enemyCreated,Texture* getTexture) {

		if (Middleware::nSpeedCount % 1500 == 0) {
			int random = rand() % 200;
			GameObject* cloud = new Cloud(getTexture->getCloudTexture(), -150, random);
			ui_elements_list.insert(ui_elements_list.begin(), cloud);
		}

		if (Middleware::nSpeedCount % 800 == 0 && game_score < Middleware::LEVEL_ONE_BOSS_SCORE) {
			int select_random = rand() % 2;
			int position_random = 100 + rand() % 200;

			if (select_random == 0) {
				GameObject* grey_bird = new GreyBird(getTexture->getGreyBirdTexture(), -64, position_random);
				bird_list.insert(bird_list.begin(), grey_bird);
			}
			if (select_random == 1) {
				GameObject* yellow_bird = new YellowBird(getTexture->getYellowBirdTexture(), -64, position_random);
				bird_list.insert(bird_list.begin(), yellow_bird);
			}
			Music* music = new Music();
			Mix_PlayChannel(-1, music->BirdChirp, 0);

		}
		else if (game_score >= Middleware::LEVEL_ONE_BOSS_SCORE && enemyCreated == false) {
			int position_random = 100 + rand() % 200;
			GameObject* eagle = new Eagle(getTexture->getEagleTexture(), -100, position_random);
			bird_list.insert(bird_list.begin(), eagle);
			enemyCreated = true;
		}
	}
};
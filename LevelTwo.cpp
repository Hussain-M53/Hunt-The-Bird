#include "Cloud.h"
#include "RedBird.h"
#include "Dragon.h"
#include "SDL.h"
#include "Music.h"
#include "Texture.h"

class LevelTwo {
public:
	LevelTwo(){}
	~LevelTwo(){}
	void handleChanges(vector<GameObject*>& ui_elements_list, vector<GameObject*>& bird_list, int& game_score, bool& enemyCreated) {
		//--------------------------------insert-----------------------------------------
		if (Middleware::nSpeedCount % 1500 == 0) {
			int random = rand() % 200;
			GameObject* cloud = new Cloud(Texture::getInstance()->getCloudTexture(), -150, random);
			ui_elements_list.insert(ui_elements_list.begin(), cloud);
		}

		if (Middleware::nSpeedCount % 800 == 0 && game_score < Middleware::LEVEL_TWO_BOSS_SCORE) {
			int select_random = rand() % 1;
			int position_random = 100 + rand() % 200;

			if (select_random == 0) {
				GameObject* red_bird = new RedBird(Texture::getInstance()->getRedBirdTexture(), -64, position_random);
				bird_list.insert(bird_list.begin(), red_bird);
			}

		}
		else if (game_score >= Middleware::LEVEL_TWO_BOSS_SCORE && enemyCreated == false) {
			GameObject* dragon = new Dragon(Texture::getInstance()->getDragonTexture(), -200, 0);
			bird_list.insert(bird_list.begin(), dragon);
			enemyCreated = true;
		}
	}
};
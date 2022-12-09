#pragma once
#include <SDL_render.h>

class Texture {
	SDL_Texture* ArcherTexture;
	SDL_Texture* GreyBirdTexture;
	SDL_Texture* RedBirdTexture;
	SDL_Texture* YellowBirdTexture;
	SDL_Texture* EagleTexture;
	SDL_Texture* ExplosionTexture;
	SDL_Texture* Explosion2Texture;
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
	SDL_Texture* livesTexture;
	SDL_Texture* HealthBarTexture;
	SDL_Texture* BowsLeftTexture;
	SDL_Texture* LevelNumberTexture;
	SDL_Texture* Background_Level_Two_Texture;
	SDL_Texture* Background_Level_One_Texture;

public:
	Texture();
	~Texture();
	SDL_Texture* LoadTexture(const char* filename);
	SDL_Texture* getArcherTexture();
	SDL_Texture* getGreyBirdTexture();
	SDL_Texture* getRedBirdTexture();
	SDL_Texture* getYellowBirdTexture();
	SDL_Texture* getEagleTexture();
	SDL_Texture* getExplosionTexture();
	SDL_Texture* getExplosion2Texture();
	SDL_Texture* getGreyEggTexture();
	SDL_Texture* getRedEggTexture();
	SDL_Texture* getYellowEggTexture();
	SDL_Texture* getEagleEggTexture();
	SDL_Texture* getDragonFireTexture();
	SDL_Texture* getCloudTexture();
	SDL_Texture* getDragonTexture();
	SDL_Texture* getSunTexture();
	SDL_Texture* getBackgroundTexture();
	SDL_Texture* getBowTexture();
	SDL_Texture* getscoreTexture();
	SDL_Texture* getlivesTexture();
	SDL_Texture* getHealthBarTexture();
	SDL_Texture* getBowsLeftTexture();
	SDL_Texture* getLevelNumberTexture();
	SDL_Texture* getBackground_Level_Two_Texture();
	SDL_Texture* getBackground_Level_One_Texture();
	void setscoreTexture(SDL_Texture* texture);
	void setlivesTexture(SDL_Texture* texture);
	void setBowsLeftTexture(SDL_Texture* texture);
	void setLevelNumberTexture(SDL_Texture* texture);
	void setBackgroundTexture(SDL_Texture* texture);
};
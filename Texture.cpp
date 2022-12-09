#include "Texture.h"
#include <SDL_image.h>
#include "Middleware.h"

Texture::Texture() {
	BowTexture = nullptr;
	scoreTexture=nullptr;
	livesTexture=nullptr;
	BowsLeftTexture=nullptr;
	LevelNumberTexture=nullptr;
	Background_Level_One_Texture = LoadTexture("Images/background.jpg");
	Background_Level_Two_Texture = LoadTexture("Images/background_level_two.jpg");
	ArcherTexture = LoadTexture("Images/archer.png");
	GreyBirdTexture = LoadTexture("Images/grey_bird.png");
	YellowBirdTexture = LoadTexture("Images/yellow_bird.png");
	RedBirdTexture = LoadTexture("Images/red_bird.png");
	CloudTexture = LoadTexture("Images/cloud.png");
	DragonTexture = LoadTexture("Images/dragon.png");
	EagleTexture = LoadTexture("Images/eagle.png");
	SunTexture =LoadTexture("Images/sun.png");
	GreyEggTexture = LoadTexture("Images/grey_egg.png");
	RedEggTexture = LoadTexture("Images/red_egg.png");
	YellowEggTexture = LoadTexture("Images/yellow_egg.png");
	EagleEggTexture = LoadTexture("Images/eagle_egg.png");
	BowTexture = LoadTexture("Images/bow.png");
	ExplosionTexture = LoadTexture("Images/feathers.png");
	Explosion2Texture = LoadTexture("Images/explosion.png");
	DragonFireTexture = LoadTexture("Images/dragon_fire.png");
	HealthBarTexture = LoadTexture("Images/health_bar.png");
	BackgroundTexture = Background_Level_One_Texture;
}
Texture::~Texture() {
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
	SDL_DestroyTexture(Explosion2Texture);
}
SDL_Texture* Texture::LoadTexture(const char* filename) {
	SDL_Surface* tempSurface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Middleware::renderer, tempSurface);
	if (texture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", filename, SDL_GetError());
	}
	SDL_FreeSurface(tempSurface);
	return texture;
}

SDL_Texture* Texture::getArcherTexture()
{
	return ArcherTexture;
}

SDL_Texture* Texture::getGreyBirdTexture()
{
	return GreyBirdTexture;
}

SDL_Texture* Texture::getRedBirdTexture()
{
	return RedBirdTexture;
}

SDL_Texture* Texture::getYellowBirdTexture()
{
	return YellowBirdTexture;
}

SDL_Texture* Texture::getEagleTexture()
{
	return EagleTexture;
}

SDL_Texture* Texture::getExplosionTexture()
{
	return ExplosionTexture;
}

SDL_Texture* Texture::getExplosion2Texture()
{
	return Explosion2Texture;
}

SDL_Texture* Texture::getGreyEggTexture()
{
	return GreyEggTexture;
}

SDL_Texture* Texture::getRedEggTexture()
{
	return RedEggTexture;
}

SDL_Texture* Texture::getYellowEggTexture()
{
	return YellowEggTexture;
}

SDL_Texture* Texture::getEagleEggTexture()
{
	return EagleEggTexture;
}

SDL_Texture* Texture::getDragonFireTexture()
{
	return DragonFireTexture;
}

SDL_Texture* Texture::getCloudTexture()
{
	return CloudTexture;
}

SDL_Texture* Texture::getDragonTexture()
{
	return DragonTexture;
}

SDL_Texture* Texture::getSunTexture()
{
	return SunTexture;
}

SDL_Texture* Texture::getBackgroundTexture()
{
	return BackgroundTexture;
}

SDL_Texture* Texture::getBowTexture()
{
	return BowTexture;
}

SDL_Texture* Texture::getscoreTexture()
{
	return scoreTexture;
}

SDL_Texture* Texture::getlivesTexture()
{
	return livesTexture;
}

SDL_Texture* Texture::getHealthBarTexture()
{
	return HealthBarTexture;
}

SDL_Texture* Texture::getBowsLeftTexture()
{
	return BowsLeftTexture;
}

SDL_Texture* Texture::getLevelNumberTexture()
{
	return LevelNumberTexture;
}

SDL_Texture* Texture::getBackground_Level_Two_Texture()
{
	return Background_Level_Two_Texture;
}

SDL_Texture* Texture::getBackground_Level_One_Texture()
{
	return Background_Level_One_Texture;
}

void Texture::setscoreTexture(SDL_Texture* texture)
{
	scoreTexture = texture;
}

void Texture::setlivesTexture(SDL_Texture* texture)
{
	livesTexture = texture;
}

void Texture::setBowsLeftTexture(SDL_Texture* texture)
{
	BowsLeftTexture = texture;
}

void Texture::setLevelNumberTexture(SDL_Texture* texture)
{
	LevelNumberTexture = texture;
}

void Texture::setBackgroundTexture(SDL_Texture* texture)
{
	BackgroundTexture = texture;
}

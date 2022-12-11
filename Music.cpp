#include "Music.h"
#include <iostream>
#include "SDL_mixer.h"


Music* Music::musicInstance = nullptr;

Music::Music(){

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	//load the music and sound effects
	gameMusic = Mix_LoadMUS("Music/Game_Music.mp3");
	dragonFire = Mix_LoadWAV("Music/Sound Effects/dragonFire.wav");
	BirdChirp = Mix_LoadWAV("Music/Sound Effects/birdChirp.mp3");
	bird1Hit = Mix_LoadWAV("Music/Sound Effects/bird1_hit.wav");
	bird2Hit = Mix_LoadWAV("Music/Sound Effects/bird2_hit.wav");
	eagleHit = Mix_LoadWAV("Music/Sound Effects/eagle_hit.wav");
	eggShoot = Mix_LoadWAV("Music/Sound Effects/enemyShoot.wav");
	jumpSound = Mix_LoadWAV("Music/Sound Effects/jump.wav");
	bowSound = Mix_LoadWAV("Music/Sound Effects/bow.wav");
	menuMusic = Mix_LoadMUS("Music/Menu_Music.mp3");
	menuSelect = Mix_LoadWAV("Music/Sound Effects/blipSelect.wav");
}

Music::~Music() {
	//Free the music
	Mix_FreeMusic(gameMusic);
	gameMusic = NULL;
	Mix_FreeMusic(menuMusic);
	menuMusic = NULL;

	//Free the sound effects
	Mix_FreeChunk(dragonFire);
	Mix_FreeChunk(eagleHit);
	Mix_FreeChunk(bird1Hit);
	Mix_FreeChunk(bird2Hit);
	Mix_FreeChunk(BirdChirp);
	Mix_FreeChunk(eggShoot);
	Mix_FreeChunk(BirdChirp);
	Mix_FreeChunk(jumpSound);
	Mix_FreeChunk(bowSound);
	Mix_Quit();
}

Music* Music::getMusicInstance()
{
	if (musicInstance == nullptr)
		musicInstance = new Music();
	return musicInstance;
}

Mix_Music* Music::getGameMusic()
{
	return gameMusic;
}

Mix_Music* Music::getMenuMusic()
{
	return menuMusic;
}

Mix_Chunk* Music::getDragonFire()
{
	return dragonFire;
}

Mix_Chunk* Music::getBirdChirp()
{
	return BirdChirp;
}

Mix_Chunk* Music::getEagleHit()
{
	return eagleHit;
}

Mix_Chunk* Music::getBird1Hit()
{
	return bird1Hit;
}

Mix_Chunk* Music::getEggShoot()
{
	return eggShoot;
}

Mix_Chunk* Music::getJumpSound()
{
	return jumpSound;
}

Mix_Chunk* Music::getBowSound()
{
	return bowSound;
}

Mix_Chunk* Music::getMenuSelect()
{
	return menuSelect;
}

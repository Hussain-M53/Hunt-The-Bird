#include "Music.h"

Music* Music::musicInstance = nullptr;

Music::Music(){
	//load the music and sound effects
	gameMusic = Mix_LoadMUS("Music/Game_Music.mp3");
	dragonFire = Mix_LoadWAV("Music/Sound Effects/dragonFire.wav");
	BirdChirp = Mix_LoadWAV("Music/Sound Effects/birdChirp.mp3");
	bird1Hit = Mix_LoadWAV("Music/Sound Effects/bird1_hit.wav");
	bird2Hit = Mix_LoadWAV("Music/Sound Effects/bird2_hit.wav");
	eagleHit = Mix_LoadWAV("Music/Sound Effects/eagle_hit.wav");
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

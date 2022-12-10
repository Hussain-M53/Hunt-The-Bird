#pragma once
#include <cstddef>
#include <SDL_mixer.h>


class Music {
	static Music* musicInstance;
	Mix_Music* gameMusic = NULL;
	Mix_Chunk* dragonFire = NULL;
	Mix_Chunk* BirdChirp = NULL;
	Mix_Chunk* eagleHit = NULL;
	Mix_Chunk* bird1Hit = NULL;
	Mix_Chunk* bird2Hit = NULL;
	Mix_Chunk* eggShoot = NULL;
	Mix_Chunk* jumpSound = NULL;
	Mix_Chunk* bowSound = NULL;
	Mix_Music* menuMusic = NULL;
	Mix_Chunk* menuSelect = NULL;
	Music();
	~Music();
public:
	static Music* getMusicInstance();
	Mix_Music* getGameMusic();
	Mix_Music* getMenuMusic();
	Mix_Chunk* getDragonFire();
	Mix_Chunk* getBirdChirp();
	Mix_Chunk* getEagleHit();
	Mix_Chunk* getBird1Hit();
	Mix_Chunk* getEggShoot();
	Mix_Chunk* getJumpSound();
	Mix_Chunk* getBowSound();
	Mix_Chunk* getMenuSelect();


};
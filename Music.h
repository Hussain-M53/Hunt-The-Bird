#pragma once
#include <cstddef>
#include <SDL_mixer.h>

struct Music {
	Mix_Music* gameMusic = NULL;
	Mix_Chunk* dragonFire = NULL;
	Mix_Chunk* BirdChirp = NULL;
	Mix_Chunk* eagleHit = NULL;
	Mix_Chunk* bird1Hit = NULL;
	Mix_Chunk* bird2Hit = NULL;
	Mix_Chunk* eggShoot = NULL;
	Mix_Chunk* jumpSound = NULL;
	Mix_Chunk* bowSound = NULL;
	Music();
	~Music();
};
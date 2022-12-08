#include "SDL.h" 
#include <stdio.h>
#include <vector>
#include "SDL_ttf.h"
#include <string>
#include "GameObject.h"
#include "Middleware.h"

class FileManager {
private:
	Game();
	~Game();
	static FileManager* file_instance;
public:
	static FileManager* getInstance();
#include "SDL.h"
#include "FileManager.h"
#include <iostream>
using namespace std;

FileManager* FileManager::file_instance = nullptr;

FileManager* FileManager::getInstance() {

	if (file_instance == nullptr) {
		file_instance = new FileManager();
	}
	return file_instance;
}
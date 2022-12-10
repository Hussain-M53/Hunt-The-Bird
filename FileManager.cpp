#include "FileManager.h"
#include "Cloud.h"
#include "Archer.h"
#include "GreyBird.h"
#include "YellowBird.h"
#include "RedBird.h"
#include "Dragon.h"
#include "Eagle.h"
#include "GreyBirdEgg.h"
#include "YellowBirdEgg.h"
#include "RedBirdEgg.h"
#include "EagleBirdEgg.h"
#include "DragonFire.h"
#include "Sun.h"
#include "Texture.h"
#include "DragonFire.h"
#include "GameObject.h"
#include "Game.h"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

FileManager* FileManager::file_instance = nullptr;
FileManager::FileManager() {}
FileManager::~FileManager(){}

FileManager* FileManager::getInstance() {

	if (file_instance == nullptr) {
		file_instance = new FileManager();
	}
	return file_instance;
}

void FileManager::readFileAndContinue(vector<GameObject*>& bird_list, vector<GameObject*>& egg_list, vector<GameObject*>& ui_elements_list) {
	string myText;
	string Tag;
	string state;

	ifstream readFile("Game State/game_state.txt");

	while (getline(readFile, myText)) {

		// A game Tag is found
		if ((myText.find('<')) != string::npos && (myText.find('>')) != string::npos) {
			//Archer
			if (Tag == "<Archer>") {
				GameObject* archer = Archer::getInstance();
				archer->setPreviousGameState(state);
			}
			//Enemies
			if (Tag == "<GreyBird>") {
				GameObject* gameObject = new GreyBird(Texture::getInstance()->getGreyBirdTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<YellowBird>") {
				GameObject* gameObject = new YellowBird(Texture::getInstance()->getYellowBirdTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<RedBird>") {
				GameObject* gameObject = new RedBird(Texture::getInstance()->getRedBirdTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<Dragon>") {
				GameObject* gameObject = new Dragon(Texture::getInstance()->getDragonTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			if (Tag == "<Eagle>") {
				GameObject* gameObject = new Eagle(Texture::getInstance()->getEagleTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				bird_list.insert(bird_list.begin(), gameObject);
			}
			//Eggs and Fire
			if (Tag == "<GreyBirdEgg>") {
				GameObject* gameObject = new GreyBirdEgg(Texture::getInstance()->getGreyEggTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<YellowBirdEgg>") {
				GameObject* gameObject = new YellowBirdEgg(Texture::getInstance()->getYellowEggTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<RedBirdEgg>") {
				GameObject* gameObject = new RedBirdEgg(Texture::getInstance()->getRedEggTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<EagleBirdEgg>") {
				GameObject* gameObject = new EagleBirdEgg(Texture::getInstance()->getEagleEggTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<DragonFire>") {
				GameObject* gameObject = new DragonFire(Texture::getInstance()->getDragonFireTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				egg_list.insert(egg_list.begin(), gameObject);
			}
			if (Tag == "<Sun>") {
				GameObject* gameObject = new Sun(Texture::getInstance()->getSunTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				ui_elements_list.insert(ui_elements_list.begin(), gameObject);
			}
			if (Tag == "<Cloud>") {
				GameObject* gameObject = new Cloud(Texture::getInstance()->getCloudTexture(), 0, 0);
				gameObject->setPreviousGameState(state);
				ui_elements_list.insert(ui_elements_list.begin(), gameObject);
			}
			if (Tag == "<GameState>") {
				Game::getInstance()->initializePreviousGameState(state);
			}

			Tag = myText;
			state = "";
			continue;
		}
		state += myText + "\n";
	}
}



void FileManager::makeFileWithStates(vector<GameObject*>& bird_list, vector<GameObject*>& egg_list) {

	//Open File
	ofstream file;
	file.open("Game State/game_state.txt");

	//save Player State
	if (Archer::getInstance() != nullptr) {
		string getPlayerState = Archer::getInstance()->saveState();
		file << getPlayerState;
	}

	//save List States
	file << Middleware::getListStates(bird_list);
	file << Middleware::getListStates(egg_list);

	// save Game States
	file << Game::getInstance()->saveGameStateVariables();

	//add a closing Tag
	file << "<>";
	file.close();
	//Close File
}

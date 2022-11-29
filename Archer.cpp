#include "Archer.h"
#include <sstream>
#include <iostream>
using namespace std;


Archer::Archer(SDL_Texture* texture, int x, int y) :GameObject(texture, x, y) {
	name = "archer";
}


void Archer::move() {
}

string Archer::saveState() {
	return"";
}

void Archer::setPreviousState(string state) {

}
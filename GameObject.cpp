#include "GameObject.h"

GameObject::GameObject(SDL_Texture* texture, int x, int y){
	this->texture = texture;
	this->name = "gameObject";
	this->alive = true;
	this->x_pos = x;
	this->y_pos = y;
	this->lives = 1;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	src_rect = { 0,0,width,height};
	dst_rect = { x,y,width,height };

}
GameObject::~GameObject(){}

//getters and setters
void GameObject::setAliveToFalse() {
	alive = false;
}

int GameObject::getX(){
	return x_pos;
}

int GameObject::getY(){
	return y_pos;
}

int GameObject::getWidth() {
	return width;
}

int GameObject::getHeight() {
	return height;
}
int GameObject::getLives(){
	return lives;
}
bool GameObject::getAlive(){
	return alive;
}
string GameObject::getName(){
	return name;
}
SDL_Rect GameObject::getDstRect(){
	return dst_rect;
}

//related to saving state
string GameObject::saveState(){
	return "";
}
void GameObject::setPreviousState(string state){}

//related to game objects behaviour
void GameObject::render(){}
void GameObject::move(){}
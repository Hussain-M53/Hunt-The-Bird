#include "GameObject.h"
#include "Middleware.h"

GameObject::GameObject(SDL_Texture* texture, double x, double y){
	this->texture = texture;
	this->name = "gameObject";
	this->alive = true;
	this->x_pos = x;
	this->y_pos = y;
	this->lives = 1;
	this->state = "still";
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	src_rect = { 0,0,width,height};
	dst_rect = { (int)x,(int)y,width,height };
	flip = SDL_FLIP_NONE;
}
GameObject::~GameObject(){}

//getters and setters
void GameObject::setAliveToFalse() {
	alive = false;
}

double GameObject::getX(){
	return x_pos;
}

double GameObject::getY(){
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
string GameObject::getState()
{
	return state;
}

double GameObject::getAngleInDegrees() {
	return angle_in_degree;
}

void GameObject::setState(string state)
{
	this->state = state;
}
SDL_Rect GameObject::getDstRect(){
	return dst_rect;
}

//related to saving state
string GameObject::saveState(){
	return "";
}
void GameObject::setPreviousGameState(string state){}

bool GameObject::animate(){
	return false;
}

void GameObject::update() {

	dst_rect.x = int(x_pos);
	dst_rect.y = int(y_pos);
}



//related to game objects behaviour
void GameObject::render() {
	this->update();
	SDL_RenderCopyEx(Middleware::renderer, texture, &src_rect, &dst_rect, angle_in_degree, NULL, flip);
}
void GameObject::move(){}
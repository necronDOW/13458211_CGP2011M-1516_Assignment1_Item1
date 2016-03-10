#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(Game* game, int x, int y)
{
	this->game = game;
	this->position = glm::vec2(x, y);
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	if (sprite != nullptr)
		sprite->Update();
}

void GameObject::Render()
{
	if (sprite != nullptr)
		sprite->Render();
}

void GameObject::SetPosition(int x, int y)
{
	position = glm::vec2(x, y);
}

void GameObject::SetSprite(float scale, char* frameID)
{
	sprite = new Sprite(game, position, scale, frameID);
	sprite->SetOrigin(&position);
}

void GameObject::SetSprite(float scale, char* frameID, char* staticID)
{
	sprite = new AnimatedSprite(game, position, scale, frameID, staticID);
	sprite->SetOrigin(&position);
}

glm::vec2 &GameObject::GetPosition() { return position; }
Sprite* &GameObject::GetSprite() { return sprite; }
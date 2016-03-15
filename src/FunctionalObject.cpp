#include "FunctionalObject.h"

FunctionalObject::FunctionalObject()
{

}
FunctionalObject::FunctionalObject(Game* game, Scene* scene, float x, float y)
	: GameObject(game, x, y)
{
	this->scene = scene;
	isGrounded = false;
	canClimb = false;
}

FunctionalObject::~FunctionalObject()
{

}

void FunctionalObject::Update()
{
	GameObject::Update();
}

void FunctionalObject::HandleInput(SDL_Event &event)
{

}

void FunctionalObject::HandleCollision(GameObject* o)
{

}
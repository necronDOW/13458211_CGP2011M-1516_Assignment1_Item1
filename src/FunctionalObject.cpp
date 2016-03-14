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
	if (scene->TileExists(position, 0, 1) < 0)
		isGrounded = false;

	if (!isGrounded)
		velocity.y += scene->GetGravity();
	
	GameObject::Update();

	sprite->FlipHorizontal(velocity.x);

	canClimb = false;
}

void FunctionalObject::HandleCollision(GameObject* o)
{

}
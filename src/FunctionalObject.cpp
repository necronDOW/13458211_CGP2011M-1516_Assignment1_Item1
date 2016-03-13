#include "FunctionalObject.h"

FunctionalObject::FunctionalObject()
{

}
FunctionalObject::FunctionalObject(Game* game, Scene* scene, float x, float y)
	: GameObject(game, x, y)
{
	this->scene = scene;
	isGrounded = false;
}

FunctionalObject::~FunctionalObject()
{

}

void FunctionalObject::Update()
{
	velocity.y = 0.0f;

	if (!scene->TileExists(this, 0, 1))
		isGrounded = false;

	if (!isGrounded)
		velocity.y += scene->GetGravity();

	if (velocity.x != 0.0f)
	{
		sprite->FlipHorizontal(velocity.x);
		sprite->ChangeAnimation("walk");
	}
	else sprite->SetToStaticAnimation();
	
	GameObject::Update();
}

void FunctionalObject::HandleCollision(GameObject* o)
{

}
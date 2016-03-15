#include "FunctionalObject.h"
#include "Ladder.h"

FunctionalObject::FunctionalObject()
{

}
FunctionalObject::FunctionalObject(Game* game, Scene* scene, float x, float y)
	: GameObject(game, x, y)
{
	this->scene = scene;

	canClimb = false;
	isClimbing = false;
}

FunctionalObject::~FunctionalObject()
{

}

void FunctionalObject::Update()
{
	if (scene->TileExists(position, 0, 0) == 1 || scene->TileExists(position, 0, 1) == 1)
		canClimb = true;
	else
	{
		canClimb = false;
		isClimbing = false;
	}

	if (scene->TileExists(position, 0, 1) > -1 && !isClimbing)
		scene->SnapToY(position);
	else if (!canClimb)
		velocity.y = scene->GetGravity();

	if (velocity.y != 0.0f && isClimbing)
		sprite->ChangeAnimation("climb");
	else if (velocity.x != 0.0f)
		sprite->ChangeAnimation("walk");
	else sprite->SetToStaticAnimation();

	sprite->FlipHorizontal(velocity.x);

	GameObject::Update();
}

void FunctionalObject::HandleInput(SDL_Event &event)
{

}

void FunctionalObject::HandleCollision(GameObject* o)
{
	if (dynamic_cast<Ladder*>(o) && isClimbing)
		position.x = o->GetPosition().x;
}
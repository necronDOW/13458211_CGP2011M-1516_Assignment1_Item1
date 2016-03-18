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
	isJumping = false;
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

	if (scene->TileExists(position, 0, 1) > -1 && !isClimbing && !isJumping)
		scene->SnapToY(position);
	else if (!canClimb && !isJumping)
		velocity.y = scene->GetGravity();

	if (isJumping)
	{
		velocity.y = jumpVelocity;
		jumpVelocity += 0.5f;

		if (jumpVelocity > scene->GetGravity())
			isJumping = false;
	}

	AnimationHandler();

	GameObject::Update();
}

void FunctionalObject::HandleInput(SDL_Event &event)
{

}

void FunctionalObject::HandleCollision(GameObject* o)
{

}

void FunctionalObject::AnimationHandler()
{
	if (velocity.y != 0.0f && isClimbing)
		sprite->ChangeAnimation("climb");
	else if (velocity.x != 0.0f)
		sprite->ChangeAnimation("walk");
	else sprite->SetToStaticAnimation();

	sprite->FlipHorizontal(velocity.x);
}

void FunctionalObject::SetJumpVelocity(float value)
{
	jumpVelocity = value;

	if (value >= 0.0f)
		isJumping = false;
	else isJumping = true;
}
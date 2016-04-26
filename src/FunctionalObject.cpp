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
		SetClimbing(false);
	}

	int tmpTileVal = scene->TileExists(position, 0, 1);
	if ((tmpTileVal == 0 || tmpTileVal == 1) && !isClimbing && !isJumping)
		scene->SnapToY(position, 0);
	else if (!canClimb && !isJumping)
		velocity.y = scene->GetGravity();

	sprite->FlipHorizontal(velocity.x);

	GameObject::Update();
}

void FunctionalObject::HandleInput(SDL_Event &event)
{

}

void FunctionalObject::HandleCollision(GameObject* o)
{

}

char* FunctionalObject::Serialize()
{
	return StrLib::str_concat(std::vector<char*> {
		"uniqueID:", StrLib::to_char(uniqueID),
		";position:", StrLib::to_char(position),
	});
}

void FunctionalObject::Deserialize(std::vector<char*> serialized)
{
	position = StrLib::char_to_vec2(StrLib::str_split(serialized[1], ":")[1]);
}

void FunctionalObject::SetClimbing(bool value)
{
	if (value == true && canClimb)
	{
		isClimbing = value;
		sprite->ChangeAnimation("climb");
	}
	else if (value == false)
		isClimbing = value;

}

void FunctionalObject::SetJumpVelocity(float value)
{
	jumpVelocity = value;

	if (value >= 0.0f)
		isJumping = false;
	else isJumping = true;
}

void FunctionalObject::SetUniqueID(int value)
{
	uniqueID = value;
}

int FunctionalObject::GetUniqueID() { return uniqueID; }
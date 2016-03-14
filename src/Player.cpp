#include "Player.h"

Player::Player()
{

}

Player::Player(Game* game, Scene* scene, float x, float y, int id)
	: FunctionalObject(game, scene, x, y)
{
	this->id = id;
}

Player::~Player()
{

}

void Player::Update()
{
	velocity.y = 0.0f;
	velocity.x = 0.0f;

	if (scene->TileExists(position, 0, 0) == 1)
		canClimb = true;
	else canClimb = false;

	HandleInput();

	if (canClimb && velocity.y != 0.0f) 
		sprite->ChangeAnimation("climb");

	if (!canClimb && velocity.x != 0.0f)
		sprite->ChangeAnimation("walk");

	if (velocity.x == 0.0f && velocity.y == 0.0f)
		sprite->SetToStaticAnimation();

	FunctionalObject::Update();
}

void Player::HandleInput()
{
	SDL_Event event = game->GetEvent();
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_A])
		velocity.x = -2.0f;
	else if (keystate[SDL_SCANCODE_D])
		velocity.x = 2.0f;
	
	if (canClimb)
	{
		if (keystate[SDL_SCANCODE_W])
			velocity.y = -2.0f;
		else if (keystate[SDL_SCANCODE_S])
			velocity.y = 2.0f;
	}
	
	if (keystate[SDL_SCANCODE_SPACE])
	{
		velocity.y -= 1.0f;
	}
}

int Player::GetID() { return id; }
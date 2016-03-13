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
	velocity.x = 0.0f;
	HandleInput();

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
	
	if (keystate[SDL_SCANCODE_SPACE])
	{
		velocity.y -= 1.0f;
	}
}

int Player::GetID() { return id; }
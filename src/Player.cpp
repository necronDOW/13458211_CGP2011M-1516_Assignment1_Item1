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
	FunctionalObject::Update();
}

void Player::HandleInput(SDL_Event &event)
{
	velocity.x = 0.0f;
	velocity.y = 0.0f;

	switch (event.type)
	{
		case SDL_KEYDOWN:
			HandleMovement(event, 2.0f);
			break;

		case SDL_KEYUP:
			break;
	}
}

void Player::HandleMovement(SDL_Event &event, float effect)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_w: 
			velocity.y = -effect;
			break;

		case SDLK_a:
			velocity.x = -effect;
			break;

		case SDLK_s:
			velocity.y = effect;
			break;

		case SDLK_d:
			velocity.x = effect;
			break;
	}
}

int Player::GetID() { return id; }
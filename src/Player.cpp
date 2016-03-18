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
	switch (event.type)
	{
		case SDL_KEYDOWN:
			if (!event.key.repeat)
				HandleMovement(event, 2.0f);
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
					if (velocity.y < 0.0f)
					{
						velocity.y = 0.0f;
						isClimbing = false;
					}
					break;

				case SDLK_a:
					if (velocity.x < 0.0f)
						velocity.x = 0.0f;
					break;

				case SDLK_s:
					if (velocity.y > 0.0f)
					{
						velocity.y = 0.0f;
						isClimbing = false;
					}
					break;

				case SDLK_d:
					if (velocity.x > 0.0f)
						velocity.x = 0.0f;
					break;
			}
			break;
	}
}

void Player::HandleMovement(SDL_Event &event, float effect)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_w: 
			if (canClimb)
			{
				velocity.y = -effect;
				isClimbing = true;
			}
			break;

		case SDLK_a:
			velocity.x = -effect;
			break;

		case SDLK_s:
			if (canClimb)
			{
				velocity.y = effect;
				isClimbing = true;
			}
			break;

		case SDLK_d:
			velocity.x = effect;
			break;

		case SDLK_SPACE:
			if (!isJumping)
				SetJumpVelocity(-4.0f);
	}
}

int Player::GetID() { return id; }
#include "Player.h"

Player::Player()
{
	score = 0;
}

Player::Player(Game* game, Scene* scene, float x, float y)
	: FunctionalObject(game, scene, x, y)
{
	score = 0;
	speed = 3.0f;
}

Player::~Player()
{

}

void Player::Update()
{
	if (game->GetClient() == nullptr)
	{
		if (isJumping)
		{
			velocity.y = jumpVelocity;
			jumpVelocity += 0.4f;

			if (jumpVelocity > scene->GetGravity())
				isJumping = false;
		}

		if (!isClimbing)
		{
			if (velocity.x != 0.0f)
				SetAnimation("walk");
			else
			{
				if (game->GetClient() == nullptr)
					sprite->SetToStaticAnimation();
			}
		}
	}

	FunctionalObject::Update();
}

void Player::HandleInput(SDL_Event &event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			if (!event.key.repeat)
				HandleMovement(event);
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
					if (velocity.y < 0.0f)
					{
						velocity.y = 0.0f;
						SetClimbing(false);
					}
					break;

				case SDLK_a:
					if (velocity.x < 0.0f)
					{
						velocity.x = 0.0f;
						game->GetAudioManager()->PauseMusic();
					}
					break;

				case SDLK_s:
					if (velocity.y > 0.0f)
					{
						velocity.y = 0.0f;
						SetClimbing(false);
					}
					break;

				case SDLK_d:
					if (velocity.x > 0.0f)
					{
						velocity.x = 0.0f;
						game->GetAudioManager()->PauseMusic();
					}
					break;
			}
			break;
	}
}

void Player::HandleMovement(SDL_Event &event)
{
	switch (event.key.keysym.sym)
	{
		case SDLK_w: 
			if (canClimb)
			{
				velocity.y = -speed;
				SetClimbing(true);
			}
			break;

		case SDLK_a:
			velocity.x = -speed;
			game->GetAudioManager()->PlayMusic();
			break;

		case SDLK_s:
			if (canClimb)
			{
				velocity.y = speed;
				SetClimbing(true);
			}
			break;

		case SDLK_d:
			velocity.x = speed;
			game->GetAudioManager()->PlayMusic();
			break;

		case SDLK_SPACE:
			if (!isJumping)
			{
				SetJumpVelocity(-4.5f);
				game->GetAudioManager()->PlayClip("jump");
			}
	}
}

void Player::HandleCollision(GameObject* o)
{
	if (dynamic_cast<Pickup*>(o))
	{
		game->GetAudioManager()->PlayClip("pickup");
		score += dynamic_cast<Pickup*>(o)->GetValue();
		o->Delete();

		glm::vec2 oTile = scene->GetCurrentTile(o->GetPosition());
		scene->SetTile(-1, oTile.x, oTile.y + 1);
		return;
	}

	if (dynamic_cast<Enemy*>(o))
	{
		game->done = true;
	}
}

char* Player::Serialize()
{
	return StrLib::str_concat(std::vector<char*> {
		"uniqueID:", StrLib::to_char(uniqueID),
			";position:", StrLib::to_char(position),
			";velocity:", StrLib::to_char(velocity),
			";", sprite->Serialize()
	});
}

void Player::Deserialize(std::vector<char*> serialized)
{
	position = StrLib::char_to_vec2(StrLib::str_split(serialized[1], ":")[1]);
	velocity = StrLib::char_to_vec2(StrLib::str_split(serialized[2], ":")[1]);
	sprite->Deserialize(StrLib::str_split(serialized[3], ":")[1]);
}
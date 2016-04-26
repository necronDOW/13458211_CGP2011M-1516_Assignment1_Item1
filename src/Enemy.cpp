#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(Game* game, Scene* scene, float x, float y)
	: FunctionalObject(game, scene, x, y)
{
	srand((unsigned int)std::time(NULL));
	if (rand() % 10 < 5) direction.x = 1;
	else direction.x = -1;

	speed = 1.0f;
	velocity.x = (float)direction.x * speed;
	checkClimb = true;
	checkWalk = false;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	if (isClimbing)
		Climb();
	else Walk();

	FunctionalObject::Update();
}

void Enemy::ChangeDirectionX()
{
	direction.x *= -1;
	velocity.x = direction.x;
}

void Enemy::SetDirection(float x, float y)
{
	direction = glm::vec2(x, y);
	velocity = direction;
}

char* Enemy::Serialize()
{
	return StrLib::str_concat(std::vector<char*> {
		"uniqueID:", StrLib::to_char(uniqueID),
		";position:", StrLib::to_char(position),
		";velocity:", StrLib::to_char(velocity)
	});
}

void Enemy::Deserialize(std::vector<char*> serialized)
{
	position = StrLib::char_to_vec2(StrLib::str_split(serialized[1], ":")[1]);
	velocity = StrLib::char_to_vec2(StrLib::str_split(serialized[2], ":")[1]);
	//sprite->Deserialize(StrLib::str_split(serialized[3], ":")[1]);
}

void Enemy::HandleCollision(GameObject* o)
{
	if (dynamic_cast<Ladder*>(o) && checkClimb)
	{
		srand((unsigned int)std::time(NULL));
		if (rand() % 3 == 1)
		{
			position.x = o->GetPosition().x;

			bool upperLadder = scene->TileExists(glm::vec2(position.x, bounds.top), 0, -1) == 1;
			bool lowerLadder = scene->TileExists(glm::vec2(position.x, bounds.bottom), 0, 1) == 1;

			if (lowerLadder && upperLadder)
			{
				if (rand() % 2 == 1) SetDirection(0, 1);
				else SetDirection(0, -1);
			}
			else if (lowerLadder) SetDirection(0, 1);
			else if (upperLadder) SetDirection(0, -1);

			startClimbY = position.y;
			SetClimbing(true);
		}

		checkClimb = false;
	}
}

void Enemy::Climb()
{
	if (checkWalk)
	{
		int checkDir[2] = { -1, 1 };

		for (int i = 0; i < 2; i++)
		{
			if (scene->TileExists(position, checkDir[i], direction.y > 0.0f ? 1 : 2) == 0)
			{
				SetDirection((float)checkDir[i], 0.0);
				sprite->ChangeAnimation("walk");
				startWalkX = position.x;

				SetClimbing(false);
				checkWalk = false;
			}
		}
	}
	else if (abs(startClimbY - position.y) > scene->GetTileSize().y * 2)
		checkWalk = true;

	if (scene->TileExists(position, 0, 1) == -1 || scene->TileExists(position, 0, 0) == -1)
		direction.y *= -1;

	velocity.y = (float)direction.y * speed;
}

void Enemy::Walk()
{
	glm::vec2 checkPosition = position;
	checkPosition.x -= direction.x * (sprite->GetRect().w / 2);

	if (abs(startWalkX - position.x) > scene->GetTileSize().x)
	{
		checkClimb = true;

		if (scene->TileExists(checkPosition, (int)direction.x, 1) == -1)
		{
			ChangeDirectionX();
			startWalkX = position.x;
		}
	}

	velocity.x = (float)direction.x * speed;
}

glm::vec2 Enemy::GetDirection() { return direction; }
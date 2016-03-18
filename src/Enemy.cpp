#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(Game* game, Scene* scene, float x, float y)
	: FunctionalObject(game, scene, x, y)
{
	int tmp = rand() % 10;

	if (tmp < 5) direction.x = 1;
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

void Enemy::HandleCollision(GameObject* o)
{

}

void Enemy::Climb()
{
	if (checkWalk)
	{
		int checkDir[2] = { -1, 1 };

		for (int i = 0; i < 2; i++)
		{
			if (scene->TileExists(position, checkDir[i], 1) == 0)
			{
				isClimbing = false;
				direction = glm::vec2(checkDir[i], 0);
				scene->SnapToX(position, 0);
			}
		}
	}
	else if (scene->TileExists(position, 1, 1) == -1 && scene->TileExists(position, -1, 1) == -1)
		checkWalk = true;

	velocity.y = direction.y;
}

void Enemy::Walk()
{
	if (scene->TileExists(position, direction.x, 1) == -1)
		direction *= -1;

	if (checkClimb)
	{
		if (scene->TileExists(position, 0, 0) == 1)
		{
			if (rand() % 10 < 5)
			{
				isClimbing = true;
				startClimbY = position.y;
				direction = glm::vec2(0, 1);

				scene->SnapToX(position, 0);
			}

			checkClimb = false;
		}
	}
	else if (scene->TileExists(position, 0, 0) == -1)
		checkClimb = true;

	velocity.x = (float)direction.x * speed;
}
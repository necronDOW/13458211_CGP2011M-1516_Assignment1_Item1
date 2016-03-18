#ifndef ENEMY_H
#define ENEMY_H

#include "FunctionalObject.h"
#include "Ladder.h"

class Enemy : public FunctionalObject
{
	public:
		Enemy();
		Enemy(Game* game, Scene* scene, float x, float y);
		~Enemy();

		void Update();
		void HandleCollision(GameObject* o);
		void Climb();
		void Walk();

	private:
		glm::vec2 direction;
		float speed;
		float startClimbY;
		bool checkClimb, checkWalk;
};

#endif
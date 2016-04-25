#ifndef ENEMY_H
#define ENEMY_H

#include <ctime>
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
		void ChangeDirectionX();
		void SetDirection(float x, float y);
		char* Serialize();
		void Deserialize(std::vector<char*> serialized);

		glm::vec2 GetDirection();

	private:
		void Climb();
		void Walk();

		glm::vec2 direction;
		float speed;
		float startClimbY, startWalkX;
		bool checkClimb, checkWalk;
};

#endif
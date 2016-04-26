#ifndef PLAYER_H
#define PLAYER_H

#include "FunctionalObject.h"
#include "Enemy.h"
#include "Pickup.h"

class Player : public FunctionalObject
{
	public:
		Player();
		Player(Game* game, Scene* scene, float x, float y);
		~Player();

		void Update();
		void HandleInput(SDL_Event &event);
		void HandleMovement(SDL_Event &event);
		void HandleCollision(GameObject* o);
		char* Serialize();
		void Deserialize(std::vector<char*> serialized);

	private:
		int score;
};

#endif
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
		void HandleMovement(SDL_Event &event, float effect);
		void HandleCollision(GameObject* o);

	private:
		int score;
};

#endif
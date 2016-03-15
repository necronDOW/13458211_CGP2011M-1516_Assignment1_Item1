#ifndef PLAYER_H
#define PLAYER_H

#include "FunctionalObject.h"

class Player : public FunctionalObject
{
	public:
		Player();
		Player(Game* game, Scene* scene, float x, float y, int id);
		~Player();

		void Update();
		void HandleInput(SDL_Event &event);
		void HandleMovement(SDL_Event &event, float effect);

		int GetID();

	private:
		int id;
};

#endif
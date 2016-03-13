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
		void HandleInput();

		int GetID();

	private:
		int id;
};

#endif
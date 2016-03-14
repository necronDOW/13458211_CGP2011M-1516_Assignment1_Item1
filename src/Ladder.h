#ifndef LADDER_H
#define LADDER_H

#include "Tile.h"

class Ladder : public Tile
{
	public:
		Ladder(Game* game, float x, float y);
		Ladder(Game* game, float x, float y, float scale, char* id);
		~Ladder();

		void HandleCollision(GameObject* o);
};

#endif
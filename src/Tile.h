#ifndef TILE_H
#define TILE_H

#include "FunctionalObject.h"

class Tile : public GameObject
{
	public:
		Tile(Game* game, float x, float y);
		Tile(Game* game, float x, float y, float scale, char* id);
		~Tile();

		virtual void HandleCollision(GameObject* o);
};

#endif
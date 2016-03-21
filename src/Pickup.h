#ifndef PICKUP_H
#define PICKUP_H

#include "Tile.h"

class Pickup : public Tile
{
	public:
		enum Type
		{
			entity_object,
			player_object
		};

		Pickup(Game* game, float x, float y, float scale, char* id);
		~Pickup();

		void HandleCollision(GameObject* o);

		Pickup::Type GetType();
		int GetValue();

	private:
		Type type = Type::entity_object;
		int scoreValue = 0;
};

#endif
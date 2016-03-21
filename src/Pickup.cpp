#include "Pickup.h"

Pickup::Pickup(Game* game, float x, float y, float scale, char* id)
	: Tile(game, x, y, scale, id)
{
	if (StringHelper::str_contains(id, "egg"))
	{
		type = Type::player_object;
		scoreValue = 100;
	}
	else if (StringHelper::str_contains(id, "food"))
	{
		scoreValue = 50;
	}
}

Pickup::~Pickup()
{

}

void Pickup::HandleCollision(GameObject* o)
{

}

Pickup::Type Pickup::GetType() { return type; }
int Pickup::GetValue() { return scoreValue; }
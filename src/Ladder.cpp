#include "Ladder.h"

Ladder::Ladder(Game* game, float x, float y)
	: Tile(game, x, y)
{

}

Ladder::Ladder(Game* game, float x, float y, float scale, char* id)
	: Tile(game, x, y, scale, id)
{

}

Ladder::~Ladder()
{

}

void Ladder::HandleCollision(GameObject* o)
{
	
}
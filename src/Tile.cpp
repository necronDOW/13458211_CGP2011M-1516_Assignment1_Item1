#include "Tile.h"
#include "Scene.h"

Tile::Tile(Game* game, float x, float y)
	: GameObject(game, x, y)
{

}

Tile::Tile(Game* game, float x, float y, float scale, char* id)
	: GameObject(game, x, y)
{
	SetSprite(1.0f, id);
}

Tile::~Tile()
{

}

void Tile::HandleCollision(GameObject* o)
{
	// Bounds information and velocity information.
	Bounds oB = o->GetBounds();
	glm::vec2 oV = o->GetVelocity();
	Bounds oldB = Bounds(oB.top - oV.y, oB.left - oV.x, oB.bottom - oV.y, oB.right - oV.x);
	SDL_Rect oRect = o->GetSprite()->GetRect();
	Bounds dfsgdf = GetBounds();

	// Check collision with left side of tile.
	if ((oldB.right <= GetBounds().left && oB.right > GetBounds().left) ||
		(oldB.left >= GetBounds().right && oB.left < GetBounds().right))
	{
		o->SetPosition(o->GetPosition().x - oV.x, o->GetPosition().y);
		return;
	}

	// Check collision with top side of tile.
	if ((oldB.bottom <= GetBounds().top && oB.bottom > GetBounds().top) ||
		(oldB.top >= GetBounds().bottom && oB.top < GetBounds().bottom))
	{
		o->SetPosition(o->GetPosition().x, o->GetPosition().y - oV.y);
		return;
	}
}
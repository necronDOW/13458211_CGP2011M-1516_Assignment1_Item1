#include "Tile.h"
#include "Scene.h"
#include "Enemy.h"

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
	Bounds oB = o->GetBounds();
	glm::vec2 oV = o->GetVelocity();
	Bounds oldB = Bounds(oB.top - oV.y, oB.left - oV.x, oB.bottom - oV.y, oB.right - oV.x);
	SDL_Rect oRect = o->GetSprite()->GetRect();
	Bounds dfsgdf = GetBounds();

	if ((oldB.right < GetBounds().left && oB.right >= GetBounds().left) ||
		(oldB.left > GetBounds().right && oB.left <= GetBounds().right))
	{
		o->SetPosition(o->GetPosition().x - oV.x, o->GetPosition().y);

		if (dynamic_cast<Enemy*>(o))
			dynamic_cast<Enemy*>(o)->ChangeDirectionX();
		return;
	}

	if (oldB.bottom <= GetBounds().top && oB.bottom > GetBounds().top)
	{
		o->SetPosition(o->GetPosition().x, o->GetPosition().y - oV.y);
		dynamic_cast<FunctionalObject*>(o)->SetJumpVelocity(0.0f);
		return;
	}

	if ((oldB.top >= GetBounds().bottom && oB.top < GetBounds().bottom))
	{
		o->SetPosition(o->GetPosition().x, o->GetPosition().y - oV.y);
		return;
	}
}
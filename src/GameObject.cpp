#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(Game* game, float x, float y)
{
	this->game = game;
	this->position = glm::vec2(x, y);
	deleted = false;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	position += velocity;

	if (sprite != nullptr)
	{
		sprite->Update();

		SDL_Rect tmp = sprite->GetRect();
		bounds = Bounds(tmp.y, tmp.x, tmp.y + tmp.h, tmp.x + tmp.w);
	}
}

void GameObject::Render()
{
	if (sprite != nullptr)
		sprite->Render();
}

glm::vec2 GameObject::AbsolutePosition()
{
	if (sprite != nullptr)
		return position + sprite->GetOffset();
	else return position;
}

void GameObject::CheckCollision(GameObject* other)
{
	glm::vec2 distance = glm::vec2(abs(AbsolutePosition().x - other->AbsolutePosition().x),
		abs(AbsolutePosition().y - other->AbsolutePosition().y));
	SDL_Rect thisRect = sprite->GetRect();
	SDL_Rect otherRect = other->GetSprite()->GetRect();

	if (distance.x <= ((thisRect.w + otherRect.w) / 2)
		&& distance.y <= ((thisRect.h + otherRect.h) / 2))
	{
		HandleCollision(other);
		other->HandleCollision(this);
	}
}

void GameObject::Delete()
{
	deleted = true;
}

bool GameObject::Deleted()
{
	return deleted;
}

void GameObject::HandleCollision(GameObject* o) { }

void GameObject::SetPosition(float x, float y)
{
	position = glm::vec2(x, y);
}

void GameObject::SetSprite(float scale, char* frameID)
{
	sprite = new Sprite(game, position, scale, frameID);
	sprite->SetOrigin(&position);
}

void GameObject::SetSprite(float scale, char* frameID, char* staticID)
{
	sprite = new AnimatedSprite(game, position, scale, frameID, staticID);
	sprite->SetOrigin(&position);
}

void GameObject::SetVelocity(float x, float y)
{
	velocity = glm::vec2(x, y);
}

glm::vec2 GameObject::GetPosition() { return position; }
glm::vec2 GameObject::GetVelocity() { return velocity; }
GameObject::Bounds GameObject::GetBounds() { return bounds; }
Sprite* &GameObject::GetSprite() { return sprite; }
#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(Game* game, glm::vec2 &origin, float scale)
{
	instance = game->GetSDLInstance();

	game->GetTextureManager()->GetSlice(0, "*", texture, src);
	SetOrigin(origin);
	SetScale(scale, scale);
}

Sprite::Sprite(Game* game, glm::vec2 &origin, float scale, char* frameID)
{
	instance = game->GetSDLInstance();

	game->GetTextureManager()->GetSlice(0, frameID, texture, src);
	SetOrigin(origin);
	SetScale(scale, scale);

	dest.w = src.w;
	dest.h = src.h;
}

Sprite::~Sprite()
{

}

void Sprite::Update()
{
	dest.x = origin.x - (dest.w / 2);
	dest.y = origin.y - (dest.h / 2);
}

void Sprite::Render()
{
	SDL_RenderCopy(instance->GetRenderer(), texture, &src, &dest);
}

void Sprite::ChangeAnimation(char* id) { }
void Sprite::LoadAllAnimations(char* id) { }

void Sprite::SetScale(float x, float y)
{
	scale = glm::vec2(x, y);

	dest.w = (float)src.w * scale.x;
	dest.h = (float)src.h * scale.y;
}

void Sprite::SetOrigin(glm::vec2 &origin)
{
	this->origin = origin;
}

const glm::vec2 &Sprite::GetScale() { return scale; }
const glm::vec2 &Sprite::GetOrigin() { return origin; }
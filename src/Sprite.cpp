#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(Game* game, glm::vec2 position, float scale)
{
	instance = game->GetSDLInstance();

	game->GetTextureManager()->GetSlice(0, "*", texture, src);
	origin = new glm::vec2(position.x, position.y);
	SetScale(scale, scale);
}

Sprite::Sprite(Game* game, glm::vec2 position, float scale, char* frameID)
{
	instance = game->GetSDLInstance();

	game->GetTextureManager()->GetSlice(0, frameID, texture, src);
	origin = new glm::vec2(position.x, position.y);
	SetScale(scale, scale);
}

Sprite::~Sprite()
{

}

void Sprite::Update()
{
	dest.x = origin->x - (dest.w / 2);
	dest.y = origin->y - (dest.h / 2);
}

void Sprite::Render()
{
	SDL_RenderCopyEx(instance->GetRenderer(), texture, src, &dest, 0, NULL, flipFlags);
}

void Sprite::ChangeAnimation(char* id) { }

void Sprite::FlipHorizontal()
{
	flipFlags = flipFlags == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void Sprite::SetScale(float x, float y)
{
	scale = glm::vec2(x, y);

	dest.w = (float)src->w * scale.x;
	dest.h = (float)src->h * scale.y;
}

void Sprite::SetOrigin(glm::vec2* origin)
{
	this->origin = origin;
}

glm::vec2 Sprite::GetScale() { return scale; }
glm::vec2 Sprite::GetOrigin() { return *origin; }
SDL_Rect Sprite::GetRect() { return dest; }
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
	dest.x = (origin->x + offset.x) - (dest.w / 2);
	dest.y = (origin->y + offset.y) - (dest.h / 2);
}

void Sprite::Render()
{
	SDL_RenderCopyEx(instance->GetRenderer(), texture, src, &dest, 0, NULL, flipFlags);
}

void Sprite::ChangeAnimation(char* id) { }
void Sprite::SetToStaticAnimation() { }

void Sprite::FlipHorizontal(float xVelocity)
{
	if (xVelocity < 0.0f)
		flipFlags = SDL_FLIP_HORIZONTAL;
	else flipFlags = SDL_FLIP_NONE;
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

void Sprite::SetOffset(float x, float y)
{
	offset = glm::vec2(x, y);
}

glm::vec2 Sprite::GetScale() { return scale; }
glm::vec2 Sprite::GetOrigin() { return *origin; }
glm::vec2 Sprite::GetOffset() { return offset; }
SDL_Rect Sprite::GetRect() { return dest; }
Timer &Sprite::GetTimer() { return Timer(); }
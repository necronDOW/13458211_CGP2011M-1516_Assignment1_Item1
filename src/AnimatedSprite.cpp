#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	: Sprite::Sprite()
{

}

AnimatedSprite::AnimatedSprite(Game* game, glm::vec2 &origin, float scale, char* animID)
{
	std::vector<char*> ids;

	instance = game->GetSDLInstance();

	game->GetTextureManager()->GetSlice(0, animID, texture, frames, ids);
	GenerateAnimations(ids);
	SetOrigin(origin);
	SetScale(scale, scale);

	src = *frames[currentFrame];

	dest.w = src.w;
	dest.h = src.h;
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::Update()
{
	Sprite::Update();

	if (++currentFrame < frames.size())
		src = *frames[currentFrame];
	else currentFrame = 0;
}

void AnimatedSprite::GenerateAnimations(std::vector<char*> &ids)
{
	char* last = "*";

	for (unsigned int i = 0; i < ids.size(); i++)
	{
		if (!StringHelper::str_contains(ids[i], last))
		{
			if (anims.size() > 0)
				anims[anims.size() - 1].last = i - 1;

			anims.push_back(Animation(StringHelper::str_split(ids[i], ".")[0], i));
			last = ids[i];
		}
	}

	anims[anims.size() - 1].last = ids.size() - 1;
}
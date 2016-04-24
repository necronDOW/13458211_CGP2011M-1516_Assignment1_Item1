#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	: Sprite::Sprite()
{

}

AnimatedSprite::AnimatedSprite(Game* game, glm::vec2 position, float scale, char* animID, char* staticID)
{
	std::vector<char*> ids;

	instance = game->GetSDLInstance();

	game->GetTextureManager()->GetSlice(0, animID, texture, frames, ids);
	GenerateAnimations(staticID, ids);

	origin = new glm::vec2(position);
	ChangeAnimation(staticID);
	SetScale(scale, scale);

	animTimer = Timer(0.1f);
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::Update()
{
	Sprite::Update();

	if (currentAnim != nullptr)
	{
		if (animTimer.IsDone())
		{
			if (currentFrame < currentAnim->last)
				currentFrame++;
			else currentFrame = currentAnim->first;
		}

		src = frames[currentFrame];
	}
	else src = frames[staticFrame];
}

void AnimatedSprite::SetToStaticAnimation()
{
	currentAnim = nullptr;
}

void AnimatedSprite::ChangeAnimation(char* newID)
{
	if (currentAnim != nullptr && !StrLib::str_contains(newID, currentAnim->id))
		return;
	
	for (unsigned int i = 0; i < anims.size(); i++)
	{
		if (StrLib::str_contains(anims[i].id, newID))
		{
			currentFrame = anims[i].first;
			currentAnim = &anims[i];
			src = frames[currentFrame];
			return;
		}
	}
}

void AnimatedSprite::GenerateAnimations(char* staticID, std::vector<char*> ids)
{
	char* last = "*";

	for (unsigned int i = 0; i < ids.size(); i++)
	{
		if (staticFrame == -1 && StrLib::str_contains(ids[i], staticID))
			staticFrame = i;

		if (!StrLib::str_contains(ids[i], last))
		{
			if (anims.size() > 0)
				anims[anims.size() - 1].last = i - 1;

			char* tmp;
			StrLib::str_copy(ids[i], tmp);
			anims.push_back(Animation(StrLib::str_split(tmp, ".")[0], i));
			last = tmp;
		}
	}

	anims[anims.size() - 1].last = ids.size() - 1;
}

Timer &AnimatedSprite::GetTimer() { return animTimer; }
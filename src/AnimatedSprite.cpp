#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
	: Sprite::Sprite()
{

}

AnimatedSprite::AnimatedSprite(Game* game, glm::vec2 position, float scale, char* animID, char* staticID)
{
	std::vector<char*> ids;

	// Set reference to SDL_Instance.
	instance = game->GetSDLInstance();

	// Get all frames and ids of the sprite and generate animations.
	game->GetTextureManager()->GetSlice(0, animID, texture, frames, ids);
	GenerateAnimations(staticID, ids);

	// Set position, static animation and scale of sprite.
	origin = new glm::vec2(position);
	ChangeAnimation(staticID);
	SetScale(scale, scale);

	// Set the animation timer to tick at 0.1f.
	animTimer = Timer(0.1f);
}

AnimatedSprite::~AnimatedSprite()
{

}

void AnimatedSprite::Update()
{
	// Call to base class Update.
	Sprite::Update();

	// Check to ensure the currentAnim is not NULL, set the src to the staticFrame if NULL.
	if (currentAnim != nullptr)
	{
		// When the timer finishes increase the current frame, accounting for the currentAnim restraints.
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
	// Set currentAnim to nullptr, which will change the animation to the staticFrame on next update.
	currentAnim = nullptr;
}

void AnimatedSprite::ChangeAnimation(char* newID)
{
	// Ensure that the newID is not the same as the current.
	if (currentAnim != nullptr && StrLib::str_contains(currentAnim->id, newID))
		return;
	
	// Check each animation id to find a match, if no match is found then animation will remain the same.
	for (unsigned int i = 0; i < anims.size(); i++)
	{
		if (StrLib::str_contains(anims[i].id, newID))
		{
			// Set the current animation to match that of the newID.
			currentFrame = anims[i].first;
			currentAnim = &anims[i];
			src = frames[currentFrame];
			return;
		}
	}
}

char* AnimatedSprite::Serialize()
{
	// Return the serialized animation id, frame and slip information.
	if (currentAnim == nullptr)
		return "anim:NULL";
	else
	{
		return StrLib::str_concat(std::vector<char*> {
			"anim:", currentAnim->id,
				",", RendererFlip_to_char(flipFlags)
		});
	}
}

void AnimatedSprite::Deserialize(char* serialized)
{
	// Deserialize all information back into their appropriate variables.
	if (!StrLib::str_contains(serialized, "NULL"))
	{
		std::vector<char*> elements = StrLib::str_split(serialized, ",");

		ChangeAnimation(elements[0]);
		flipFlags = char_to_RendererFlip(elements[1]);
	}
}

void AnimatedSprite::GenerateAnimations(char* staticID, std::vector<char*> ids)
{
	char* last = "*";

	// Parse all animation information in the data structs.
	for (unsigned int i = 0; i < ids.size(); i++)
	{
		// If the staticID is found, set it locally.
		if (staticFrame == -1 && StrLib::str_contains(ids[i], staticID))
			staticFrame = i;

		// When a new animation name is found when compared to the last, add it to the animations vector.
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

	// Set the last value for the final animation to the maximum index.
	anims[anims.size() - 1].last = ids.size() - 1;
}

Timer &AnimatedSprite::GetTimer() { return animTimer; }
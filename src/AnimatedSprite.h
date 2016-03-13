#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include "Timer.h"

class AnimatedSprite : public Sprite
{
	struct Animation {
		char* id;
		unsigned int first;
		unsigned int last;

		Animation(char* id_, unsigned int index) 
			: id(id_), first(index) { }
	};

	public:
		AnimatedSprite();
		AnimatedSprite(Game* game, glm::vec2 position, float scale, char* animID, char* staticID);
		~AnimatedSprite();

		void Update();
		void SetToStaticAnimation();
		void ChangeAnimation(char* newID);

		Timer &GetTimer();

	private:
		void GenerateAnimations(char* staticID, std::vector<char*> ids);

		int staticFrame = -1;
		unsigned int currentFrame = 0;
		std::vector<SDL_Rect*> frames;
		Animation* currentAnim = nullptr;
		std::vector<Animation> anims;
		Timer animTimer;
};

#endif
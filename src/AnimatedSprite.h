#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"

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
		AnimatedSprite(Game* game, glm::vec2 &origin, float scale, char* animID);
		~AnimatedSprite();

		void Update();

	private:
		void GenerateAnimations(std::vector<char*> &ids);

		unsigned int currentFrame = 0;
		std::vector<SDL_Rect*> frames;
		std::vector<Animation> anims;
		Animation* currentAnimation;
};

#endif
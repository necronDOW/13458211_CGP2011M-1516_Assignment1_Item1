#ifndef SPRITE_H
#define SPRITE_H

// C++ includes
#include "Game.h"

// SDL includes
#include "glm/glm.hpp"

class Sprite
{
	public:
		Sprite();
		Sprite(Game* game, glm::vec2 &origin, float scale);
		Sprite(Game* game, glm::vec2 &origin, float scale, char* frameID);
		~Sprite();

		virtual void Update();
		virtual void Render();
		virtual void ChangeAnimation(char* id);
		virtual void LoadAllAnimations(char* id);

		void SetScale(float x, float y);
		void SetOrigin(glm::vec2 &origin);
		const glm::vec2 &GetScale();
		const glm::vec2 &GetOrigin();

	protected:
		SDL_Instance* instance;
		SDL_Texture* texture;
		SDL_Rect &src = SDL_Rect();
		SDL_Rect dest;
		glm::vec2 &origin = glm::vec2(0, 0);
		glm::vec2 scale;
};

#endif
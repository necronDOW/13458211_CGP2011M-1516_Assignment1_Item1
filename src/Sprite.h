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
		Sprite(Game* game, glm::vec2 position, float scale);
		Sprite(Game* game, glm::vec2 position, float scale, char* frameID);
		~Sprite();

		virtual void Update();
		virtual void Render();
		virtual void ChangeAnimation(char* id);
		void FlipHorizontal();

		void SetScale(float x, float y);
		void SetOrigin(glm::vec2* origin);
		glm::vec2 GetScale();
		glm::vec2 GetOrigin();
		SDL_Rect GetRect();

	protected:
		SDL_Instance* instance;
		SDL_Texture* texture;
		SDL_Rect* src;
		SDL_Rect dest;
		glm::vec2* origin;
		glm::vec2 scale;
		SDL_RendererFlip flipFlags = SDL_FLIP_NONE;
};

#endif
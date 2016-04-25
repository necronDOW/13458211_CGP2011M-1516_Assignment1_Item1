#ifndef SPRITE_H
#define SPRITE_H

// C++ includes
#include "Game.h"
#include "Timer.h"

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
		virtual void SetToStaticAnimation();
		void FlipHorizontal(float xVelocity);
		virtual char* Serialize();
		virtual void Deserialize(char* serialized);

		void SetScale(float x, float y);
		void SetOrigin(glm::vec2* origin);
		void SetOffset(float x, float y);
		glm::vec2 GetScale();
		glm::vec2 GetOrigin();
		glm::vec2 GetOffset();
		SDL_Rect GetRect();
		virtual Timer &GetTimer();

	protected:
		SDL_Instance* instance;
		SDL_Texture* texture;
		SDL_Rect* src;
		SDL_Rect dest;
		glm::vec2* origin;
		glm::vec2 offset;
		glm::vec2 scale;
		SDL_RendererFlip flipFlags = SDL_FLIP_NONE;
};

#endif
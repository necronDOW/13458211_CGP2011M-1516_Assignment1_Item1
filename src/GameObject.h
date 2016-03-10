#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"
#include "AnimatedSprite.h"

#include "glm/glm.hpp"

class GameObject
{
	public:
		// Constructors/Destructors
		GameObject();
		GameObject(Game* game, int x, int y);
		~GameObject();

		// General functions
		void Update();
		void Render();

		// Get/Set functions
		void SetPosition(int x, int y);
		void SetSprite(float scale, char* frameID);
		void SetSprite(float scale, char* frameID, char* staticID);
		glm::vec2 &GetPosition();
		Sprite* &GetSprite();

	private:
		Game* game;
		glm::vec2 position;
		Sprite* sprite;
};

#endif
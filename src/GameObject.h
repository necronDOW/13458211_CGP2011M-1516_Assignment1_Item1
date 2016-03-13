#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <typeinfo>
#include "Game.h"
#include "AnimatedSprite.h"
#include "Scene.h"

#include "glm/glm.hpp"

class GameObject
{
	public:
		struct Bounds {
			float top;
			float left;
			float bottom;
			float right;
			Bounds() { }
			Bounds(float t, float l, float b, float r)
				: top(t), left(l), bottom(b), right(r) { }
		};

		// Constructors/Destructors
		GameObject();
		GameObject(Game* game, float x, float y);
		~GameObject();

		// General functions
		virtual void Update();
		virtual void Render();
		glm::vec2 AbsolutePosition();
		void CheckCollision(GameObject* other);
		virtual void HandleCollision(GameObject* o);

		// Get/Set functions
		void SetPosition(float x, float y);
		void SetSprite(float scale, char* frameID);
		void SetSprite(float scale, char* frameID, char* staticID);
		void SetVelocity(float x, float y);
		glm::vec2 GetPosition();
		glm::vec2 GetVelocity();
		Bounds GetBounds();
		Sprite* &GetSprite();

	protected:
		Game* game;
		glm::vec2 position;
		glm::vec2 velocity;
		Bounds bounds;
		Sprite* sprite;
};

#endif
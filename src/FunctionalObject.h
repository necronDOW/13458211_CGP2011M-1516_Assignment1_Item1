#ifndef FUNCTIONALOBJECT_H
#define FUNCTIONALOBJECT_H

#include "GameObject.h"
#include "Tile.h"

class FunctionalObject : public GameObject
{
	public:
		FunctionalObject();
		FunctionalObject(Game* game, Scene* scene, float x, float y);
		~FunctionalObject();

		virtual void Update();
		virtual void HandleCollision(GameObject* o);

		bool isGrounded;

	protected:
		Scene* scene;
};

#endif
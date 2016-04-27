#ifndef FUNCTIONALOBJECT_H
#define FUNCTIONALOBJECT_H

#include "GameObject.h"

class Ladder;

class FunctionalObject : public GameObject
{
	public:
		FunctionalObject();
		FunctionalObject(Game* game, Scene* scene, float x, float y);
		~FunctionalObject();

		virtual void Update();
		virtual void HandleInput(SDL_Event &event);
		virtual void HandleCollision(GameObject* o);
		virtual char* Serialize();
		virtual void Deserialize(std::vector<char*> serialized);

		void SetJumpVelocity(float value);
		void SetUniqueID(int value);
		int GetUniqueID();

	protected:
		void SetClimbing(bool value);
		void SetAnimation(char* id);

		Scene* scene;
		bool canClimb;
		bool isClimbing;
		bool isJumping;
		float speed;
		float jumpVelocity;
		int uniqueID = -1;
};

#endif
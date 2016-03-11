#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include "StringHelper.h"
#include "Game.h"
#include "ObjectConstructor.h"

class GameObject;

class Scene
{
	public:
		Scene();
		Scene(Game* game, std::vector<char*> &levelsData, int index, ObjectConstructor* &constructor);
		~Scene();

		void Update();
		void Render();

		glm::vec2 GetTileSize();
		glm::vec2 GetSize();

	private:
		int InstantiateDynObjects(Game* game, std::vector<char*> &levelsData, int dataStart);
		
		std::vector<GameObject*> objects;
		glm::vec2 tileSize;
		glm::vec2 tileCount;
};

#endif
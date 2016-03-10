#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include "StringHelper.h"
#include "Game.h"

class GameObject;

class Scene
{
	public:
		Scene();
		Scene(Game* game, std::vector<char*> &levelsData, int index);
		~Scene();

		void Update();
		void Render();

	private:
		std::vector<char*> tileIDs = { "floor", "ladder", "egg", "food" };
		std::vector<GameObject*> objects;
};

#endif
#ifndef OBJECTCONSTRUCTOR_H
#define OBJECTCONSTRUCTOR_H

#include <iostream>
#include <vector>
#include "GameObject.h"

class ObjectConstructor
{
	public:
		ObjectConstructor(std::vector<char*> levelData);
		~ObjectConstructor();

		GameObject* CreateObject(Game* game, glm::vec2 position, char* type);
		GameObject* CreateObject(Game* game, glm::vec2 position, int type);
		
		std::vector<char*> GetValidObjects();
		std::vector<char*> GetValidTiles();

	private:
		std::vector<GameObject*> objects;
		std::vector<char*> validObjects;
		std::vector<char*> validTiles;
};

#endif
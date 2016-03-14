#ifndef OBJECTCONSTRUCTOR_H
#define OBJECTCONSTRUCTOR_H

#include <iostream>
#include <vector>
#include "Ladder.h"
#include "Player.h"

class FunctionalObject;

class ObjectConstructor
{
	public:
		ObjectConstructor(std::vector<char*> levelData);
		~ObjectConstructor();

		void CreateObject(std::vector<FunctionalObject*> &objects, Game* game, Scene* scene, glm::vec2 position, char* type);
		void CreateObject(std::vector<GameObject*> &objects, Game* game, glm::vec2 position, int type);
		
		std::vector<char*> GetValidObjects();
		std::vector<char*> GetValidTiles();

	private:
		std::vector<GameObject*> objects;
		std::vector<char*> validObjects;
		std::vector<char*> validTiles;
};

#endif
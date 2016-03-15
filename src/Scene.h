#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include "StringHelper.h"
#include "Game.h"

class GameObject;
class FunctionalObject;
class ObjectConstructor;

class Scene
{
	public:
		Scene();
		Scene(Game* game, std::vector<char*> &levelsData, int index, ObjectConstructor* &constructor);
		~Scene();

		void Update();
		void HandleInput(SDL_Event &event);
		void Render();
		int GetTileID(int x, int y);
		int TileExists(glm::vec2 pos, int relativeCoordX, int relativeCoordY);

		void SetGravity(float value);
		glm::vec2 GetTileSize();
		glm::vec2 GetSize();
		float GetGravity();

	private:
		int InstantiateDynObjects(Game* game, std::vector<char*> &levelsData, int dataStart, ObjectConstructor* &constructor);
		
		std::vector<int> tileMap;
		std::vector<GameObject*> tiles;
		std::vector<FunctionalObject*> objects;
		glm::vec2 tileSize;
		glm::vec2 tileCount;
		float gravity;
};

#endif
#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <vector>
#include "Game.h"
#include "StrLib.h"

class GameObject;
class FunctionalObject;
class ObjectConstructor;
class Player;

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
		void SnapToX(glm::vec2 &pos, int offset);
		void SnapToY(glm::vec2 &pos, int offset);
		glm::vec2 GetCurrentTile(glm::vec2 pos);
		FunctionalObject* FindObjectWithID(int id);
		void SetTile(int value, int x, int y);

		void SetGravity(float value);
		glm::vec2 GetTileSize();
		glm::vec2 GetSize();
		float GetGravity();
		int GetObjectiveCount();

		int playerCount = 0;

	private:
		int InstantiateDynObjects(std::vector<char*> &levelsData, int dataStart, ObjectConstructor* &constructor);
		
		Game* game;
		std::vector<int> tileMap;
		std::vector<GameObject*> tiles;
		std::vector<FunctionalObject*> objects;
		glm::vec2 tileSize;
		glm::vec2 tileCount;
		float gravity;
		int objectiveCount;
};

#endif
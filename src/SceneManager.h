#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"
#include "StringHelper.h"
#include "Scene.h"
#include "ObjectConstructor.h"

class SceneManager
{
	public:
		SceneManager();
		SceneManager(Game* game, char* filePath);
		~SceneManager();

		void Update();
		void Render();
		void NextScene();
		void PreviousScene();

		const Scene &GetScene(int index);
		int GetCurrentIndex();
		glm::vec2 GetScalar();

	private:
		void LoadScenes(Game* game, std::vector<char*> &lines, std::vector<int> &indices);

		std::vector<Scene> scenes;
		unsigned int currentScene = -1;
		ObjectConstructor* constructor;
};

#endif
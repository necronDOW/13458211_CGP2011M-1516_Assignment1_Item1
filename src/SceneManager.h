#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"
#include "StringHelper.h"
#include "Scene.h"

class SceneManager
{
	public:
		SceneManager();
		SceneManager(Game* game, char* filePath);
		~SceneManager();

		void Update();
		void Render();
		void LoadScenes(Game* game, std::vector<char*> &lines, std::vector<int> &indices);
		void NextScene();
		void PreviousScene();

	private:
		std::vector<Scene*> scenes;
		unsigned int currentScene = -1;
};

#endif
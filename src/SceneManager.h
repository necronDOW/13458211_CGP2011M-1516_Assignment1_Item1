#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Game.h"
#include "StrLib.h"
#include "Scene.h"
#include "ObjectConstructor.h"

class SceneManager
{
	public:
		SceneManager();
		SceneManager(Game* game, char* filePath);
		~SceneManager();

		void Initialize(Game* game);
		void Update();
		void HandleInput(SDL_Event &event);
		void Render();
		void NextScene();
		void PreviousScene();
		void UpdateSceneObject(char* serialized);

		Scene* &GetScene(int index);
		int GetCurrentIndex();
		glm::vec2 GetScalar();

	private:
		void LoadScenes(Game* game, std::vector<char*> &lines, std::vector<int> &indices);

		char* filePath = "";
		std::vector<Scene*> scenes;
		unsigned int currentScene = -1;
		ObjectConstructor* constructor;
		SDL_Instance* instance;
		AudioManager* audioMngr;
};

#endif
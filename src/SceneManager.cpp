#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::SceneManager(Game* game, char* filePath)
{
	std::vector<int> levelIndices;
	std::vector<char*> lines;
	std::ifstream file(filePath);
	std::string buffer;

	if (!file)
	{
		std::cout << std::endl << "Levels.data file was loaded unsuccessfully." << std::endl;
		return;
	}

	int i = 0;
	while (std::getline(file, buffer))
	{
		char* tmp;
		StringHelper::str_copy((char*)buffer.c_str(), tmp);
		lines.push_back(tmp);

		i++;
		if (StringHelper::str_contains(tmp, "level"))
			levelIndices.push_back(i);
	}

	LoadScenes(game, lines, levelIndices);
	if (scenes.size() > 0) currentScene = 0;
}

SceneManager::~SceneManager()
{

}

void SceneManager::Update()
{
	if (currentScene >= 0)
		scenes[currentScene]->Update();
}

void SceneManager::Render()
{
	if (currentScene >= 0)
		scenes[currentScene]->Render();
}

void SceneManager::LoadScenes(Game* game, std::vector<char*> &lines, std::vector<int> &indices)
{
	for (int i = 0; i < indices.size(); i++)
		scenes.push_back(new Scene(game, lines, indices[i]));
}

void SceneManager::NextScene()
{
	if (currentScene + 1 < scenes.size())
		currentScene++;
}

void SceneManager::PreviousScene()
{
	if (currentScene > 0)
		currentScene--;
}
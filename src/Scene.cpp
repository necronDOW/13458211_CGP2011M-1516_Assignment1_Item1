#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{

}

Scene::Scene(Game* game, std::vector<char*> &levelsData, int dataStart)
{
	for (unsigned int i = dataStart; i < levelsData.size(); i++)
	{
		if (StringHelper::str_contains(levelsData[i], "};"))
		{
			std::cout << "Scene loaded successfully: TILES:" << objects.size() << "." << std::endl;
			return;
		}

		for (unsigned int j = 0; j < strlen(levelsData[i]); j++)
		{
			int val = levelsData[i][j] - '0' - 1;

			if (val >= 0 && val < tileIDs.size())
			{
				objects.push_back(new GameObject(game, (j) * 24, (i - dataStart) * 16));
				objects[objects.size() - 1]->SetSprite(1.0f, tileIDs[val]);
			}
		}
	}

	if (objects.size() == 0)
	{
		std::cout << std::endl << "Scene loaded incorrectly." << std::endl;
	}
}

Scene::~Scene()
{

}

void Scene::Update()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Update();
}

void Scene::Render()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}
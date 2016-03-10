#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{

}

Scene::Scene(Game* game, std::vector<char*> &levelsData, int index)
{
	for (unsigned int i = 0; i < levelsData.size(); i++)
	{
		if (StringHelper::str_contains(levelsData[i], "{"))
		{
			char* tmp;
			StringHelper::str_copy(levelsData[i], tmp);
			if (atoi(StringHelper::str_split(tmp, " ")[1]) == index)
			{
				for (unsigned int j = i + 1; j < levelsData.size(); j++)
				{
					if (StringHelper::str_contains(levelsData[j], "};"))
					{
						std::cout << "Scene loaded successfully: INDEX:" << index << ", TILES:" << objects.size() << "." << std::endl;
						return;
					}

					for (unsigned int k = 0; k < strlen(levelsData[j]); k++)
					{
						int val = levelsData[j][k] - '0' - 1;

						if (val >= 0 && val < tileIDs.size())
						{
							objects.push_back(new GameObject(game, (k - 1) * 24, (j - i - 1) * 16));
							objects[objects.size() - 1]->SetSprite(1.0f, tileIDs[val]);
						}
					}
				}
			}
		}
	}

	if (objects.size() == 0)
	{
		std::cout << std::endl << "Scene loaded incorrectly, please check your index (" << index << ")." << std::endl;
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
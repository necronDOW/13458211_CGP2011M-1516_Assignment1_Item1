#include "Scene.h"
#include "GameObject.h"

Scene::Scene()
{

}

Scene::Scene(Game* game, std::vector<char*> &levelsData, int dataStart, ObjectConstructor* &constructor)
{
	Sprite tmp = Sprite(game, glm::vec2(0, 0), 1.0f, constructor->GetValidTiles()[0]);
	tileCount = glm::vec2(0, 0);
	tileSize = glm::vec2(tmp.GetRect().w, tmp.GetRect().h);

	for (unsigned int i = dataStart; i < levelsData.size(); i++)
	{
		if (StringHelper::str_contains(levelsData[i], "#"))
			i = InstantiateDynObjects(game, levelsData, i + 1);

		if (StringHelper::str_contains(levelsData[i], "};"))
		{
			std::cout << "Scene loaded successfully: TILES:" << objects.size() << "." << std::endl;
			tileCount.y = i - dataStart;
			tileCount.x++;
			return;
		}

		for (unsigned int j = 1; j < strlen(levelsData[i]); j++)
		{
			int val = levelsData[i][j] - '0' - 1;
			
			GameObject* newObject = constructor->CreateObject(game, glm::vec2(j * tileSize.x, (i - dataStart) * tileSize.y), val);
			if (newObject != nullptr)
				objects.push_back(newObject);

			if (j > tileCount.x)
				tileCount.x = j;
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

int Scene::InstantiateDynObjects(Game* game, std::vector<char*> &levelsData, int dataStart)
{
	for (unsigned int i = dataStart; i < levelsData.size(); i++)
	{
		if (StringHelper::str_contains(levelsData[i], "};"))
			return i;

		std::vector<char*> dynData = StringHelper::str_split(levelsData[i], "=,");

		glm::vec2 pos = glm::vec2(atoi(dynData[1]) * tileSize.x, atoi(dynData[2]) * tileSize.y);
		objects.push_back(new GameObject(game, pos.x, pos.y));
		objects[objects.size() - 1]->SetSprite(1.0f, "chick", "chick");
	}
}

glm::vec2 Scene::GetTileSize() { return tileSize; }
glm::vec2 Scene::GetSize() { return tileCount * tileSize; }
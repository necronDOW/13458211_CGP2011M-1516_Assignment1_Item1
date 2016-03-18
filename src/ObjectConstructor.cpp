#include "ObjectConstructor.h"
#include "FunctionalObject.h"

ObjectConstructor::ObjectConstructor(std::vector<char*> levelData)
{
	for (unsigned int i = 0; i < levelData.size(); i++)
	{
		if (StringHelper::str_contains(levelData[i], "valid"))
		{
			for (int j = i + 1; j < levelData.size(); j++)
			{
				if (StringHelper::str_contains(levelData[j], "};"))
				{
					i = j + 1;
					break;
				}

				validObjects.push_back(levelData[j] + 1);
			}
		}
		else if (StringHelper::str_contains(levelData[i], "tiles"))
		{
			for (int j = i + 1; j < levelData.size(); j++)
			{
				if (StringHelper::str_contains(levelData[j], "};"))
				{
					i = j + 1;
					break;
				}

				validTiles.push_back(levelData[j] + 1);
			}
		}
	}
}

ObjectConstructor::~ObjectConstructor()
{

}

void ObjectConstructor::CreateObject(std::vector<FunctionalObject*> &objects, Game* game, Scene* scene, glm::vec2 position, char* type)
{
	for (unsigned int i = 0; i < validObjects.size(); i++)
	{
		if (StringHelper::str_contains(validObjects[i], type))
		{
			if (StringHelper::str_contains(type, "player"))
				objects.push_back(new Player(game, scene, position.x, position.y, 1));
			else objects.push_back(new FunctionalObject(game, scene, position.x, position.y));

			objects[objects.size() - 1]->SetSprite(1.0f, type, type);

			if (StringHelper::str_contains(type, "player"))
				objects[objects.size() - 1]->GetSprite()->SetScale(0.9f, 0.9f);

			Sprite* tmp = objects[objects.size() - 1]->GetSprite();
			tmp->SetOffset(0, -tmp->GetRect().h / 2);
			return;
		}
	}
}

void ObjectConstructor::CreateObject(std::vector<GameObject*> &objects, Game* game, glm::vec2 position, int type)
{
	for (unsigned int i = 0; i < validTiles.size(); i++)
	{
		if (type >= 0 && type < validTiles.size())
		{
			switch (type)
			{
				case 1:
					objects.push_back(new Ladder(game, position.x, position.y));
					break;
				default:
					objects.push_back(new Tile(game, position.x, position.y));
					break;
			}
			objects[objects.size() - 1]->SetSprite(1.0f, validTiles[type]);
			return;
		}
	}
}

std::vector<char*> ObjectConstructor::GetValidObjects() { return validObjects; }
std::vector<char*> ObjectConstructor::GetValidTiles() { return validTiles; }
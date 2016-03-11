#include "ObjectConstructor.h"

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

GameObject* ObjectConstructor::CreateObject(Game* game, glm::vec2 position, char* type)
{
	for (unsigned int i = 0; i < validObjects.size(); i++)
	{
		if (StringHelper::str_contains(validObjects[i], type))
		{
			objects.push_back(new GameObject(game, position.x, position.y));
			objects[objects.size() - 1]->SetSprite(1.0f, type);
			return objects[objects.size() - 1];
		}
	}

	return nullptr;
}

GameObject* ObjectConstructor::CreateObject(Game* game, glm::vec2 position, int type)
{
	for (unsigned int i = 0; i < validTiles.size(); i++)
	{
		if (type >= 0 && type < validTiles.size())
		{
			objects.push_back(new GameObject(game, position.x, position.y));
			objects[objects.size() - 1]->SetSprite(1.0f, validTiles[type]);
			return objects[objects.size() - 1];
		}
	}

	return nullptr;
}

std::vector<char*> ObjectConstructor::GetValidObjects() { return validObjects; }
std::vector<char*> ObjectConstructor::GetValidTiles() { return validTiles; }
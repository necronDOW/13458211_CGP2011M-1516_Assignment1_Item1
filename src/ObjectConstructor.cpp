#include "ObjectConstructor.h"

ObjectConstructor::ObjectConstructor(std::vector<char*> levelData)
{
	for (unsigned int i = 0; i < levelData.size(); i++)
	{
		if (StrLib::str_contains(levelData[i], "valid"))
		{
			for (unsigned int j = i + 1; j < levelData.size(); j++)
			{
				if (StrLib::str_contains(levelData[j], "};"))
				{
					i = j + 1;
					break;
				}

				validObjects.push_back(levelData[j] + 1);
			}
		}
		else if (StrLib::str_contains(levelData[i], "tiles"))
		{
			for (unsigned int j = i + 1; j < levelData.size(); j++)
			{
				if (StrLib::str_contains(levelData[j], "};"))
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
		if (StrLib::str_contains(validObjects[i], type))
		{
			if (StrLib::str_contains(type, "player"))
			{
				scene->playerCount++;
				objects.push_back(new Player(game, scene, position.x, position.y, scene->playerCount));
			}
			else if (StrLib::str_contains(type, "chick"))
				objects.push_back(new Enemy(game, scene, position.x, position.y));
			else objects.push_back(new FunctionalObject(game, scene, position.x, position.y));

			FunctionalObject* tmp = objects[objects.size() - 1];
			tmp->SetSprite(1.0f, type, type);
			tmp->GetSprite()->SetScale(0.9f, 0.9f);

			tmp->GetSprite()->SetOffset(0.0, (float)(-tmp->GetSprite()->GetRect().h / 2));
			tmp->SetUniqueID(objects.size() - 1);

			if (StrLib::str_contains(type, "chuckie") || StrLib::str_contains(type, "cage"))
				tmp->usesGravity = false;
			return;
		}
	}
}

void ObjectConstructor::CreateObject(std::vector<GameObject*> &objects, Game* game, glm::vec2 position, int type)
{
	for (unsigned int i = 0; i < validTiles.size(); i++)
	{
		if (type >= 0)
		{
			if (type == 1)
			{
				objects.push_back(new Ladder(game, position.x, position.y));
			}
			else if (type == 2 || type == 3)
			{
				objects.push_back(new Pickup(game, position.x, position.y, 1.0f, validTiles[type]));
				return;
			}
			else
			{
				objects.push_back(new Tile(game, position.x, position.y));
			}

			objects[objects.size() - 1]->SetSprite(1.0f, validTiles[type]);
			return;
		}
	}
}

std::vector<char*> ObjectConstructor::GetValidObjects() { return validObjects; }
std::vector<char*> ObjectConstructor::GetValidTiles() { return validTiles; }
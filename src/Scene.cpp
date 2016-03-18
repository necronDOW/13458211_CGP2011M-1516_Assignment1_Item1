#include "Scene.h"
#include "FunctionalObject.h"
#include "ObjectConstructor.h"

Scene::Scene()
{

}

Scene::Scene(Game* game, std::vector<char*> &levelsData, int dataStart, ObjectConstructor* &constructor)
{
	gravity = 4.0f;

	Sprite tmp = Sprite(game, glm::vec2(0, 0), 1.0f, constructor->GetValidTiles()[0]);
	tileCount = glm::vec2(0, 0);
	tileSize = glm::vec2(tmp.GetRect().w, tmp.GetRect().h);

	for (unsigned int i = dataStart; i < levelsData.size(); i++)
	{
		if (StringHelper::str_contains(levelsData[i], "#"))
		{
			tileCount.y = (float)(i - dataStart);
			i = InstantiateDynObjects(game, levelsData, i + 1, constructor);
		}

		if (StringHelper::str_contains(levelsData[i], "};"))
		{
			std::cout << "Scene loaded successfully: TILES:" << tiles.size() << "." << std::endl;
			tileCount.x++;
			break;
		}

		for (unsigned int j = 1; j < strlen(levelsData[i]); j++)
		{
			int val = levelsData[i][j] - '0' - 1;
			
			tileMap.push_back(val);
			constructor->CreateObject(tiles, game, glm::vec2(j * tileSize.x, (i - dataStart) * tileSize.y), val);

			if (j > tileCount.x)
				tileCount.x = (float)j;
		}
	}

	if (tiles.size() == 0)
	{
		std::cout << std::endl << "Scene loaded incorrectly." << std::endl;
	}
}

Scene::~Scene()
{

}

void Scene::Update()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		tiles[i]->Update();

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		for (unsigned int j = 0; j < tiles.size(); j++)
			objects[i]->CheckCollision(tiles[j]);

		objects[i]->Update();
	}
}

void Scene::HandleInput(SDL_Event &event)
{
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->HandleInput(event);
}

void Scene::Render()
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		tiles[i]->Render();

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

int Scene::InstantiateDynObjects(Game* game, std::vector<char*> &levelsData, int dataStart, ObjectConstructor* &constructor)
{
	for (unsigned int i = dataStart; i < levelsData.size(); i++)
	{
		if (StringHelper::str_contains(levelsData[i], "};"))
			return i;

		std::vector<char*> dynData = StringHelper::str_split(levelsData[i], "=,");

		constructor->CreateObject(objects, game, this, glm::vec2(atoi(dynData[1]) * tileSize.x, atoi(dynData[2]) * tileSize.y), dynData[0] + 1);
	}
}

int Scene::GetTileID(int x, int y)
{
	if (x < tileCount.x - 1&& y < tileCount.y)
		return tileMap[(y * (tileCount.x - 1)) + x];
	else return -1;
}

int Scene::TileExists(glm::vec2 pos, int relativeCoordX, int relativeCoordY)
{
	glm::vec2 position = glm::vec2(pos.x - (tileSize.x / 2), pos.y - (tileSize.y / 4));
	glm::vec2 tileIndices = GetCurrentTile(position);

	return GetTileID(tileIndices.x + relativeCoordX, tileIndices.y + relativeCoordY);
}

void Scene::SnapToX(glm::vec2 &pos, int offset)
{
	pos.x = (GetCurrentTile(pos).x + offset) * tileSize.x;
}

void Scene::SnapToY(glm::vec2 &pos, int offset)
{
	glm::vec2 position = glm::vec2(pos.x - (tileSize.x / 2), pos.y);
	pos.y = (GetCurrentTile(position).y + offset) * tileSize.y + 3;
}

glm::vec2 Scene::GetCurrentTile(glm::vec2 pos)
{
	int pX = -1, pY = -1;

	while (pos.x > 0)
	{
		pos.x -= tileSize.x;
		pX++;
	}

	while (pos.y > 0)
	{
		pos.y -= tileSize.y;
		pY++;
	}

	return glm::vec2(pX, pY);
}

void Scene::SetGravity(float value)
{
	gravity = value;
}

glm::vec2 Scene::GetTileSize() { return tileSize; }
glm::vec2 Scene::GetSize() { return tileCount * tileSize; }
float Scene::GetGravity() { return gravity; }
#include "MenuManager.h"
#include "Menu.h"
#include "FileLib.h"

MenuManager::MenuManager()
{

}

MenuManager::MenuManager(Game* game, char* filePath)
{
	std::vector<int> menuIndices;
	std::vector<char*> lines;
	FileLib::LoadFromFile(filePath, lines, "*menu_", menuIndices);

	LoadMenus(game, lines, menuIndices);
}

MenuManager::~MenuManager()
{

}

void MenuManager::Update()
{
	if (activeMenu != nullptr)
		activeMenu->Update();
}

void MenuManager::HandleInput(SDL_Event &event)
{
	if (activeMenu != nullptr)
		activeMenu->HandleInput(event);
}

void MenuManager::Render()
{
	if (activeMenu != nullptr)
		activeMenu->Render();
}

Menu* MenuManager::FindMenuByTag(char* tag)
{
	for (unsigned int i = 0; i < menus.size(); i++)
	{
		if (StrLib::str_contains(menus[i]->GetTag(), tag))
			return menus[i];
	}

	return nullptr;
}

void MenuManager::LoadMenus(Game* game, std::vector<char*> data, std::vector<int> indices)
{
	for (unsigned int i = 0; i < indices.size(); i++)
		menus.push_back(new Menu(game, this, data, indices[i]));

	SetActiveMenu(FindMenuByTag("main"));
}

void MenuManager::SetActiveMenu(Menu* value)
{
	activeMenu = value;
	activeMenu->InitialAction();
}
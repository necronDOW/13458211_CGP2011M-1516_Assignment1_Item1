#include "MenuManager.h"
#include "Game.h"
#include "Menu.h"

MenuManager::MenuManager()
{

}

MenuManager::MenuManager(Game* game, char* filePath)
{
	//TODO:Make File helper class for this and SceneManager file loading.
	std::vector<int> menuIndices;
	std::vector<char*> lines;
	std::ifstream file(filePath);
	std::string buffer;

	if (!file)
	{
		std::cout << std::endl << "File was loaded unsuccessfully (" << filePath << ")." << std::endl;
		return;
	}

	int i = 0;
	while (std::getline(file, buffer))
	{
		char* tmp;
		StringHelper::str_copy((char*)buffer.c_str(), tmp);
		lines.push_back(tmp);

		if (StringHelper::str_contains(tmp, "*menu_"))
			menuIndices.push_back(i);

		i++;
	}

	LoadMenus(lines, menuIndices);
}

MenuManager::~MenuManager()
{

}

void MenuManager::Update()
{
	if (activeMenu != nullptr && visible)
		activeMenu->Update();
}

void MenuManager::Render()
{
	if (activeMenu != nullptr && visible)
		activeMenu->Render();
}

Menu* MenuManager::FindMenuByTag(char* tag)
{
	for (int i = 0; i < menus.size(); i++)
	{
		if (StringHelper::str_contains(menus[i]->GetTag(), tag))
			return menus[i];
	}

	return nullptr;
}

void MenuManager::LoadMenus(std::vector<char*> data, std::vector<int> indices)
{
	for (int i = 0; i < indices.size(); i++)
		menus.push_back(new Menu(this, data, indices[i]));

	activeMenu = FindMenuByTag("main");
	visible = false;
}

void MenuManager::SetActiveMenu(Menu* value)
{
	activeMenu = value;
}

void MenuManager::SetVisible(bool value)
{
	visible = value;
}
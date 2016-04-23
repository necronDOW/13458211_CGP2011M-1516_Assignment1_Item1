#include "Menu.h"

Menu::Menu()
{

}

Menu::Menu(MenuManager* manager, std::vector<char*> data, int startIndex)
{
	tag = StringHelper::str_split(data[startIndex], "_")[1];
}

Menu::~Menu()
{

}

void Menu::Update()
{

}

void Menu::Render()
{

}

char* Menu::GetTag() { return tag; }
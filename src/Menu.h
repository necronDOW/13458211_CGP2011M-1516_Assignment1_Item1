#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Text.h"
#include "DynamicText.h"
#include "MenuManager.h"

class Menu
{
	public:
		Menu();
		Menu(MenuManager* manager, std::vector<char*> data, int startIndex);
		~Menu();

		void Update();
		void Render();

		char* GetTag();

	private:
		MenuManager* manager;
		char* tag;
};

#endif
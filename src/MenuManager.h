#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <fstream>
#include <vector>

#include "Game.h"

class Menu;

class MenuManager
{
	public:
		MenuManager();
		MenuManager(Game* game, char* filePath);
		~MenuManager();

		void Update();
		void HandleInput(SDL_Event &event);
		void Render();
		Menu* FindMenuByTag(char* tag);

		void SetActiveMenu(Menu* value);

	private:
		void LoadMenus(Game* game, std::vector<char*> data, std::vector<int> indices);
		std::vector<Menu*> menus;
		Menu* activeMenu;
};

#endif
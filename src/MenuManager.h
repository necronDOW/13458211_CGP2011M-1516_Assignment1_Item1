#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <fstream>
#include <vector>

class Menu;
class Game;

class MenuManager
{
	public:
		MenuManager();
		MenuManager(Game* game, char* filePath);
		~MenuManager();

		void Update();
		void Render();
		Menu* FindMenuByTag(char* tag);

		void SetActiveMenu(Menu* value);
		void SetVisible(bool value);

	private:
		void LoadMenus(std::vector<char*> data, std::vector<int> indices);
		std::vector<Menu*> menus;
		Menu* activeMenu;
		bool visible;
};

#endif
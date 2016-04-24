#ifndef MENU_H
#define MENU_H

#include <vector>
#include "Text.h"
#include "DynamicText.h"
#include "MenuManager.h"
#include "AnimatedSprite.h"

class Menu
{
	enum actionType
	{
		type_state,
		type_menu
	};

	struct menuAction
	{
		SDL_Keycode keyCode;
		actionType type;
		char* actionTag;

		menuAction(char* k, char* a)
		{
			keyCode = SDL_GetKeyFromName(k);

			std::vector<char*> tmp = StringHelper::str_split(a, "_");

			if (StringHelper::str_contains(tmp[0], "menu"))
				type = actionType::type_menu;
			else if (StringHelper::str_contains(tmp[0], "state"))
				type = actionType::type_state;

			actionTag = tmp[1];
		}
	};
	struct menuComponent
	{
		Text* text;
		menuAction* action;

		menuComponent(Text* t, menuAction* a)
			: text(t), action(a) { }
	};
	struct menuSprite
	{
		AnimatedSprite* sprite;
		glm::vec2 startPos;
		glm::vec2 origin;
		glm::vec2 velocity;

		menuSprite(AnimatedSprite* s, glm::vec2 o, glm::vec2 v)
			: sprite(s), origin(o), velocity(v)
		{
			startPos = o;
			sprite->SetOrigin(&origin);
		}
	};
	struct menuTimer
	{
		Timer* timer;
		menuAction* action;

		menuTimer() { }
		menuTimer(Timer* t, menuAction* a)
			: timer(t), action(a) { }
	};

	public:
		Menu();
		Menu(Game* game, MenuManager* manager, std::vector<char*> data, int startIndex);
		~Menu();

		void Update();
		void HandleInput(SDL_Event &event);
		void Render();

		char* GetTag();

	private:
		void Reset();
		int CreateLabel(std::vector<char*> data, int startIndex);
		int CreateSprite(std::vector<char*> data, int startIndex);
		int CreateTimer(std::vector<char*> data, int startIndex);
		char* acquireValue(char* data);
		glm::vec2 acquireVector(char* data);
		SDL_Color acquireColor(char* data);
		void DoAction(menuAction* a);

		Game* game;
		MenuManager* manager;
		std::vector<menuComponent> components;
		std::vector<menuSprite*> sprites;
		menuTimer* timer = nullptr;
		char* tag;
};

#endif
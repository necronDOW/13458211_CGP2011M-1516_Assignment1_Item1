#include "Menu.h"

Menu::Menu()
{

}

Menu::Menu(Game* game, MenuManager* manager, std::vector<char*> data, int startIndex)
{
	this->game = game;
	this->manager = manager;
	tag = StrLib::str_split(data[startIndex++], "_")[1];

	for (unsigned int i = startIndex; i < data.size(); i++)
	{
		if (StrLib::str_contains(data[i], "};"))
			break;
		else if (StrLib::str_contains(data[i], "action"))
			action = StrLib::str_split(data[i], ":")[1];
		else if (StrLib::str_contains(data[i], "label"))
			i = CreateLabel(data, i);
		else if (StrLib::str_contains(data[i], "sprite"))
			i = CreateSprite(data, i);
		else if (StrLib::str_contains(data[i], "timer"))
			i = CreateTimer(data, i);
	}
}

Menu::~Menu()
{

}

void Menu::Update()
{
	if (timer != nullptr)
	{
		if (timer->timer->IsDone())
			DoAction(timer->action);
	}

	for (unsigned int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->origin += sprites[i]->velocity;
		sprites[i]->sprite->Update();
	}
}

void Menu::HandleInput(SDL_Event &event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			if (!event.key.repeat)
			{
				SDL_Keycode key = event.key.keysym.sym;

				for (unsigned int i = 0; i < components.size(); i++)
				{
					if (components[i].action != nullptr && key == components[i].action->keyCode)
						DoAction(components[i].action);
				}
			}
			break;
	}
}

void Menu::Render()
{
	for (unsigned int i = 0; i < components.size(); i++)
		components[i].text->Render();

	for (unsigned int i = 0; i < sprites.size(); i++)
		sprites[i]->sprite->Render();
}

void Menu::InitialAction()
{
	if (action != "")
		game->SetGameState(action);
}

void Menu::Reset()
{
	for (unsigned int i = 0; i < sprites.size(); i++)
		sprites[i]->origin = sprites[i]->startPos;
}

int Menu::CreateLabel(std::vector<char*> data, int startIndex)
{
	char* text = "";
	int fontPt = 0;
	glm::vec2 position = glm::vec2(0, 0);
	SDL_Color color;
	std::vector<char*> action;

	unsigned int i = startIndex;
	for (i = startIndex; i < data.size(); i++)
	{
		if (StrLib::str_contains(data[i], "}"))
			break;
		else if (StrLib::str_contains(data[i], "text:"))
			text = acquireValue(data[i]);
		else if (StrLib::str_contains(data[i], "font-size:"))
			fontPt = atoi(acquireValue(data[i]));
		else if (StrLib::str_contains(data[i], "position:"))
			position = StrLib::char_to_vec2(StrLib::str_split(data[i], ":")[1]);
		else if (StrLib::str_contains(data[i], "color:"))
			color = StrLib::char_to_color(StrLib::str_split(data[i], ":")[1]);
		else if (StrLib::str_contains(data[i], "action:"))
			action = StrLib::str_split(StrLib::str_split(data[i], ":")[1], ",");
	}

	if (action.size() > 0)
		text = StrLib::str_concat(std::vector<char*> { text, " (", action[0], ")" });

	Text* tmpText = new Text(game, position, fontPt, text, color.r, color.g, color.b);
	menuAction* tmpAction = action.size() > 0 ? new menuAction(action[0], action[1]) : nullptr;
	components.push_back(menuComponent(tmpText, tmpAction));

	return i;
}

int Menu::CreateSprite(std::vector<char*> data, int startIndex)
{
	char* id = "";
	float scale = 1.0f;
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 velocity = glm::vec2(0, 0);

	unsigned int i = startIndex;
	for (i = startIndex; i < data.size(); i++)
	{
		if (StrLib::str_contains(data[i], "}"))
			break;
		else if (StrLib::str_contains(data[i], "id:"))
			id = acquireValue(data[i]);
		else if (StrLib::str_contains(data[i], "scale:"))
			scale = atof(acquireValue(data[i]));
		else if (StrLib::str_contains(data[i], "position:"))
			position = StrLib::char_to_vec2(StrLib::str_split(data[i], ":")[1]);
		else if (StrLib::str_contains(data[i], "velocity:"))
			velocity = StrLib::char_to_vec2(StrLib::str_split(data[i], ":")[1]);
	}

	AnimatedSprite* tmpSprite = new AnimatedSprite(game, position, scale, id, "walk");
	sprites.push_back(new menuSprite(tmpSprite, position, velocity));

	return i;
}

int Menu::CreateTimer(std::vector<char*> data, int startIndex)
{
	float delay = 0.0f;
	std::vector<char*> action;

	unsigned int i = startIndex;
	for (i = startIndex; i < data.size(); i++)
	{
		if (StrLib::str_contains(data[i], "}"))
			break;
		else if (StrLib::str_contains(data[i], "delay:"))
			delay = atof(acquireValue(data[i]));
		else if (StrLib::str_contains(data[i], "action:"))
			action = StrLib::str_split(StrLib::str_split(data[i], ":")[1], ",");
	}

	Timer* tmpTimer = new Timer(delay);
	menuAction* tmpAction = new menuAction("", action[0]);
	timer = new menuTimer(tmpTimer, tmpAction);

	return i;
}

char* Menu::acquireValue(char* data)
{
	return StrLib::str_split(data, ":")[1];
}

void Menu::DoAction(menuAction* a)
{
	Reset();

	if (a->type == actionType::type_menu)
		manager->SetActiveMenu(manager->FindMenuByTag(a->actionTag));
	else if (a->type == actionType::type_state)
		game->SetGameState(a->actionTag);
}

char* Menu::GetTag() { return tag; }
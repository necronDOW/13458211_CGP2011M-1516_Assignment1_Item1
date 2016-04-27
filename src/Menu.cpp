#include "Menu.h"
#include "FileLib.h"

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
			labels.push_back(CreateLabel(data, i));
		else if (StrLib::str_contains(data[i], "sprite"))
			sprites.push_back(CreateSprite(data, i));
		else if (StrLib::str_contains(data[i], "list"))
			lists.push_back(CreateList(data, i));
		else if (StrLib::str_contains(data[i], "timer"))
			timer = CreateTimer(data, i);
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

				for (unsigned int i = 0; i < labels.size(); i++)
				{
					if (labels[i].action != nullptr && key == labels[i].action->keyCode)
						DoAction(labels[i].action);
				}
			}
			break;
	}
}

void Menu::Render()
{
	for (unsigned int i = 0; i < labels.size(); i++)
		labels[i].text->Render();

	for (unsigned int i = 0; i < sprites.size(); i++)
		sprites[i]->sprite->Render();

	for (unsigned int i = 0; i < lists.size(); i++)
	{
		for (unsigned int j = 0; j < lists[i].labels.size(); j++)
			lists[i].labels[j]->Render();
	}
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

Menu::menuComponent Menu::CreateLabel(std::vector<char*> data, size_t &i)
{
	char* text = "";
	int fontPt = 0;
	glm::vec2 position = glm::vec2(0, 0);
	SDL_Color color;
	std::vector<char*> action;

	for (i; i < data.size(); i++)
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
	return menuComponent(tmpText, tmpAction);
}

Menu::menuSprite* Menu::CreateSprite(std::vector<char*> data, size_t &i)
{
	char* id = "";
	float scale = 1.0f;
	glm::vec2 position = glm::vec2(0, 0);
	glm::vec2 velocity = glm::vec2(0, 0);

	for (i; i < data.size(); i++)
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
	return new menuSprite(tmpSprite, position, velocity);
}

Menu::menuList Menu::CreateList(std::vector<char*> data, size_t &i)
{
	std::vector<char*> lines;
	int fontPt = 0;
	glm::vec2 position = glm::vec2(0, 0);
	SDL_Color color;
	std::vector<Text*> labels;

	for (i; i < data.size(); i++)
	{
		if (StrLib::str_contains(data[i], "}"))
			break;
		else if (StrLib::str_contains(data[i], "src:"))
			FileLib::LoadFromFile(StrLib::str_split(data[i], ":")[1], lines);
		else if (StrLib::str_contains(data[i], "font-size:"))
			fontPt = atoi(acquireValue(data[i]));
		else if (StrLib::str_contains(data[i], "position:"))
			position = StrLib::char_to_vec2(StrLib::str_split(data[i], ":")[1]);
		else if (StrLib::str_contains(data[i], "color:"))
			color = StrLib::char_to_color(StrLib::str_split(data[i], ":")[1]);
	}

	float top = (float)fontPt * ((float)lines.size() / 2.0f);
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		glm::vec2 tmpPos = glm::vec2(position.x, (position.y - top) + (fontPt * i));
		labels.push_back(new Text(game, tmpPos, fontPt, lines[i], color.r, color.g, color.b));
	}

	return menuList(position, labels);
}

Menu::menuTimer* Menu::CreateTimer(std::vector<char*> data, size_t &i)
{
	float delay = 0.0f;
	std::vector<char*> action;

	for (i; i < data.size(); i++)
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
	return new menuTimer(tmpTimer, tmpAction);
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
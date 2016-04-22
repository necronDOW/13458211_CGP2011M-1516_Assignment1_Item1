#include "Text.h"

Text::Text()
{

}

Text::Text(Game* game, glm::vec2 position, int fontPt, char* text)
{
	instance = game->GetSDLInstance();
	font = TTF_OpenFont(fontStyle, fontPt);

	color = CreateSDL_Color(255, 255, 255);
	Initialize(text, fontPt, position.x, position.y);
}

Text::Text(Game* game, glm::vec2 position, int fontPt, char* text, uint8_t r, uint8_t g, uint8_t b)
{
	instance = game->GetSDLInstance();
	font = TTF_OpenFont(fontStyle, fontPt);

	color = CreateSDL_Color(r, g, b);
	Initialize(text, fontPt, position.x, position.y);
}

Text::~Text()
{

}

void Text::Render()
{
	SDL_RenderCopy(instance->GetRenderer(), texture, NULL, &dest);
}

SDL_Color Text::CreateSDL_Color(uint8_t r, uint8_t g, uint8_t b)
{
	SDL_Color tmp;

	tmp.r = r;
	tmp.g = g;
	tmp.b = b;

	return tmp;
}

void Text::SetSize(char* text, int fontPt)
{
	this->fontPt = fontPt;

	dest.w = strlen(text) * (fontPt / 2);
	dest.h = fontPt;
}

void Text::SetPosition(int x, int y)
{
	origin = glm::vec2(x, y);

	dest.x = origin.x - (dest.w / 2);
	dest.y = origin.y - (dest.h / 2);
}

void Text::Initialize(char* text, int fontPt, int x, int y)
{
	this->text = text;

	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	if (surface == NULL)
	{
		std::cout << "Failed to generate text surface! TEXT:" << text << "." << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface(instance->GetRenderer(), surface);
	if (texture == NULL)
	{
		std::cout << "Failed to generate texture from text surface! TEXT:" << text << "." << std::endl;
		return;
	}

	SDL_FreeSurface(surface);

	SetSize(text, fontPt);
	SetPosition(x, y);
}
#include "Text.h"

Text::Text()
{

}

Text::Text(Game* game, glm::vec2 position, int fontPt, char* text)
{
	instance = game->GetSDLInstance();
	origin = new glm::vec2(position.x, position.y);
	font = TTF_OpenFont("./assets/fonts/opensans_light.ttf", 100);
	this->text = text;

	SetColor(255, 255, 255);
	Initialize(fontPt);
}

Text::Text(Game* game, glm::vec2 position, int fontPt, char* text, uint8_t r, uint8_t g, uint8_t b)
{
	instance = game->GetSDLInstance();
	origin = new glm::vec2(position.x, position.y);
	font = TTF_OpenFont("./assets/fonts/opensans_light.ttf", fontPt);
	this->text = text;

	SetColor(r, g, b);
	Initialize(fontPt);
}

Text::~Text()
{
	
}

void Text::Update()
{
	dest.x = origin->x - (dest.w / 2);
	dest.y = origin->y - (dest.h / 2);
}

void Text::Render()
{
	SDL_RenderCopy(instance->GetRenderer(), texture, NULL, &dest);
}

void Text::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;
}

void Text::SetSize(int fontPt)
{
	dest.w = strlen(text) * (fontPt / 3);
	dest.h = fontPt;
}

void Text::Initialize(int fontPt)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
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
	SetSize(fontPt);
}
#include "DynamicText.h"

DynamicText::DynamicText()
{

}

DynamicText::DynamicText(Game* game, glm::vec2 position, int fontPt, char* text)
{
	instance = game->GetSDLInstance();
	font = TTF_OpenFont(fontStyle, fontPt);

	color = CreateSDL_Color(255, 255, 255);
	Initialize(textBuffer, fontPt, position.x, position.y);
	SetText(text);
}

DynamicText::DynamicText(Game* game, glm::vec2 position, int fontPt, char* text, uint8_t r, uint8_t g, uint8_t b)
{
	instance = game->GetSDLInstance();
	font = TTF_OpenFont(fontStyle, fontPt);

	color = CreateSDL_Color(r, g, b);
	Initialize(textBuffer, fontPt, position.x, position.y);
	SetText(text);
}

DynamicText::~DynamicText()
{

}

void DynamicText::Initialize(char* text, int fontPt, int x, int y)
{
	Text::Initialize(text, fontPt, x, y);

	SDL_QueryTexture(texture, NULL, NULL, &fontDimensions.x, &fontDimensions.y);
	fontDimensions.x /= strlen(textBuffer);
	this->text = "";
}

void DynamicText::Render()
{
	for (int i = 0; i < srcRects.size(); i++)
		SDL_RenderCopy(instance->GetRenderer(), texture, &srcRects[i], &destRects[i]);
}

void DynamicText::SetText(char* text)
{
	std::vector<int> tmp;

	SetSize(text, fontPt);
	SetPosition(origin.x, origin.y);

	for (int i = 0; i < strlen(text); i++)
	{
		if (i < strlen(this->text) && this->text[i] == text[i])
			tmp.push_back(-1);
		else
		{
			for (int j = 0; j < strlen(textBuffer); j++)
			{
				if (text[i] == textBuffer[j])
				{
					tmp.push_back(j);
					break;
				}
			}
		}

		if (tmp[i] != -1)
		{
			SDL_Rect tmpSrc = CreateSDL_Rect(tmp[i] * fontDimensions.x, 0, fontDimensions.x, fontDimensions.y);
			SDL_Rect tmpDest = CreateSDL_Rect(dest.x + (i * (dest.w / strlen(text))), dest.y, dest.w / strlen(text), dest.h);

			if (srcRects.size() > i)
			{
				srcRects[i] = tmpSrc;
				destRects[i] = tmpDest;
			}
			else
			{
				srcRects.push_back(tmpSrc);
				destRects.push_back(tmpDest);
			}
		}
	}

	this->text = text;
}

SDL_Rect DynamicText::CreateSDL_Rect(int x, int y, int w, int h)
{
	SDL_Rect tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.w = w;
	tmp.h = h;

	return tmp;
}
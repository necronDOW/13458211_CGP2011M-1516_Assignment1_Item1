#include "DynamicText.h"

DynamicText::DynamicText()
{

}

DynamicText::DynamicText(Game* game, glm::vec2 position, int fontPt, char* text)
{
	// Set the instance reference and font.
	instance = game->GetSDLInstance();
	font = TTF_OpenFont(fontStyle, fontPt);

	// Set the color (white) and text, along side initializing the text to the specific values.
	color = CreateSDL_Color(255, 255, 255);
	Initialize(textBuffer, fontPt, (int)position.x, (int)position.y);
	SetText(text);
}

DynamicText::DynamicText(Game* game, glm::vec2 position, int fontPt, char* text, uint8_t r, uint8_t g, uint8_t b)
{
	// Set the instance reference and font.
	instance = game->GetSDLInstance();
	font = TTF_OpenFont(fontStyle, fontPt);

	// Set the color (provided) and text, along side initializing the text to the specific values.
	color = CreateSDL_Color(r, g, b);
	Initialize(textBuffer, fontPt, (int)position.x, (int)position.y);
	SetText(text);
}

DynamicText::~DynamicText()
{

}

void DynamicText::Initialize(char* text, int fontPt, int x, int y)
{
	// Base Initialization logic.
	Text::Initialize(text, fontPt, x, y);

	// Query the texture created and calculate character width.
	SDL_QueryTexture(texture, NULL, NULL, &fontDimensions.x, &fontDimensions.y);
	fontDimensions.x /= strlen(textBuffer);
	this->text = "";
}

void DynamicText::Render()
{
	// Render all characters.
	for (unsigned int i = 0; i < srcRects.size(); i++)
		SDL_RenderCopy(instance->GetRenderer(), texture, &srcRects[i], &destRects[i]);
}

void DynamicText::SetText(char* text)
{
	std::vector<int> tmp;

	// Set the text size based on the provided text and the font size.
	SetSize(text, fontPt);

	// Set center position for object.
	SetPosition((int)origin.x, (int)origin.y);

	// Calculate a source rectangle and destination rectangle for each character in the provided text.
	for (unsigned int i = 0; i < strlen(text); i++)
	{
		// Check each character against the textbuffer, adding each position to the tmp vector.
		if (i < strlen(this->text) && this->text[i] == text[i])
			tmp.push_back(-1);
		else
		{
			for (unsigned int j = 0; j < strlen(textBuffer); j++)
			{
				if (text[i] == textBuffer[j])
				{
					tmp.push_back(j);
					break;
				}
			}
		}

		// If the new character at position i is different to the original then calculate new source and destination rectangles.
		if (tmp[i] != -1)
		{
			SDL_Rect tmpSrc = CreateSDL_Rect(tmp[i] * fontDimensions.x, 0, fontDimensions.x, fontDimensions.y);
			SDL_Rect tmpDest = CreateSDL_Rect(dest.x + (i * (dest.w / strlen(text))), dest.y, dest.w / strlen(text), dest.h);

			// If i is more than the current src vector size, then push_back new element, otherwise set at src vector i.
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

	// Set the local text to the desired text.
	this->text = text;
}

SDL_Rect DynamicText::CreateSDL_Rect(int x, int y, int w, int h)
{
	// Create a temporary SDL_Rect and populate it with the provided values.
	SDL_Rect tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.w = w;
	tmp.h = h;

	return tmp;
}
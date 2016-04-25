#include "StrLib.h"

StrLib::StrLib()
{

}

StrLib::~StrLib()
{

}

void StrLib::str_copy(char* original, char* &target)
{
	target = new char[strlen(original)];

	for (unsigned int i = 0; i < strlen(target); i++)
		target[i] = original[i];
}

std::vector<char*> StrLib::str_split(char* word, char* delimiter)
{
	std::vector<char*> tmp;
	char* token = strtok(word, delimiter);

	while (token != NULL)
	{
		tmp.push_back(token);
		token = strtok(NULL, delimiter);
	}

	return tmp;
}

bool StrLib::str_contains(char* haystack, char* needle)
{
	unsigned int hLen = strlen(haystack);
	unsigned int nLen = strlen(needle);

	for (unsigned int i = 0; i < hLen; i++)
	{
		int matchCount = 0;

		for (unsigned int j = 0; j < nLen; j++)
		{
			if (haystack[i + j] == needle[j])
				matchCount++;
			else j = nLen;

			if (matchCount == nLen)
				return true;
		}
	}

	return false;
}

char* StrLib::str_concat(std::vector<char*> elements)
{
	int bufferN = 0;

	for (unsigned int i = 0; i < elements.size(); i++)
		bufferN += strlen(elements[i]);

	char* buffer = new char[bufferN];
	strcpy(buffer, elements[0]);

	for (unsigned int i = 1; i < elements.size(); i++)
		strcat(buffer, elements[i]);

	return buffer;
}

char* StrLib::to_char(int value)
{
	char* tmp;
	str_copy((char*)std::to_string(value).c_str(), tmp);
	return tmp;
}

char* StrLib::to_char(float value)
{
	return (char*)std::to_string(value).c_str();
}

char* StrLib::to_char(bool value)
{
	return value ? "true" : "false";
}

char* StrLib::to_char(glm::vec2 value)
{
	return str_concat(std::vector<char*> { to_char((int)value.x), ",", to_char((int)value.y) });
}

char* StrLib::to_char(SDL_Color value)
{
	return str_concat(std::vector<char*> { to_char(value.r), ",", to_char(value.g), ",", to_char(value.b) });
}

bool StrLib::char_to_bool(char* value)
{
	if (str_contains(value, "true"))
		return true;
	else return false;
}

glm::vec2 StrLib::char_to_vec2(char* value)
{
	std::vector<char*> tmp = str_split(value, ",");
	return glm::vec2(atof(tmp[0]), atof(tmp[1]));
}

SDL_Color StrLib::char_to_color(char* value)
{
	std::vector<char*> tmp = str_split(value, ",");
	SDL_Color tmpCol;

	tmpCol.r = atoi(tmp[0]);
	tmpCol.g = atoi(tmp[1]);
	tmpCol.b = atoi(tmp[2]);
	return tmpCol;
}
#include "StringHelper.h"

StringHelper::StringHelper()
{

}

StringHelper::~StringHelper()
{

}

void StringHelper::str_copy(char* original, char* &target)
{
	target = new char[strlen(original)];

	for (int i = 0; i < strlen(target); i++)
		target[i] = original[i];
}

std::vector<char*> StringHelper::str_split(char* word, char* delimiter)
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
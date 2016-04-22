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

bool StringHelper::str_contains(char* haystack, char* needle)
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

char* StringHelper::str_concat(char** elements)
{
	int N = sizeof(elements) / sizeof(elements[0]);
	int bufferN = 0;

	for (int i = 0; i < N; i++)
		bufferN += strlen(elements[i]);

	char* buffer = new char[bufferN];
	strcpy(buffer, elements[0]);

	for (int i = 1; i < N; i++)
		strcat(buffer, elements[i]);

	return buffer;
}
#ifndef STRINGHELPER_H
#define STRINGHELPER_H

#include <iostream>
#include <vector>

class StringHelper
{
	public:
		StringHelper();
		~StringHelper();

		static void str_copy(char* original, char* &target);
		static std::vector<char*> str_split(char* word, char* delimiter);
		static bool str_contains(char* haystack, char* needle);
};

#endif
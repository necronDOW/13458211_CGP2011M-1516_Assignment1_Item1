#ifndef StrLib_H
#define StrLib_H

#include <iostream>
#include <vector>
#include <string>

#include <SDL.h>
#include "glm/glm.hpp"

class StrLib
{
	public:
		StrLib();
		~StrLib();

		static void str_copy(char* original, char* &target);
		static std::vector<char*> str_split(char* word, char* delimiter);
		static bool str_contains(char* haystack, char* needle);
		static char* str_concat(std::vector<char*> elements);
		static char* to_char(int value);
		static char* to_char(float value);
		static char* to_char(bool value);
		static char* to_char(glm::vec2 value);
		static char* to_char(SDL_Color value);
		static bool char_to_bool(char* value);
		static glm::vec2 char_to_vec2(char* value);
		static SDL_Color char_to_color(char* value);
};

#endif
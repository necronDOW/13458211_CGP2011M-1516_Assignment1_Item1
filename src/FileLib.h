#ifndef FILELIB_H
#define FILELIB_H

// C++ includes
#include <vector>
#include <fstream>

// Project includes
#include "StrLib.h"

class FileLib
{
	public:
		FileLib();
		~FileLib();

		static void LoadFromFile(char* filePath, std::vector<char*> &outLines);
		static void LoadFromFile(char* filePath, std::vector<char*> &outLines, char* indicesID, std::vector<int> &outIndices);
		static void AppendToFile(char* filePath, std::vector<char*> appends);
};

#endif
#include "FileLib.h"

FileLib::FileLib()
{

}

FileLib::~FileLib()
{

}

void FileLib::LoadFromFile(char* filePath, std::vector<char*> &outLines)
{
	std::ifstream file(filePath);
	std::string buffer;

	if (!file)
	{
		std::cout << std::endl << "File was loaded unsuccessfully (" << filePath << ")." << std::endl;
		return;
	}

	while (std::getline(file, buffer))
	{
		char* tmp;
		StrLib::str_copy((char*)buffer.c_str(), tmp);
		outLines.push_back(tmp);
	}
}

void FileLib::LoadFromFile(char* filePath, std::vector<char*> &outLines, char* indicesID, std::vector<int> &outIndices)
{
	std::ifstream file(filePath);
	std::string buffer;

	if (!file)
	{
		std::cout << std::endl << "File was loaded unsuccessfully (" << filePath << ")." << std::endl;
		return;
	}

	int i = 0;
	while (std::getline(file, buffer))
	{
		char* tmp;
		StrLib::str_copy((char*)buffer.c_str(), tmp);
		outLines.push_back(tmp);

		if (StrLib::str_contains(tmp, indicesID))
			outIndices.push_back(i);

		i++;
	}
}

void FileLib::AppendToFile(char* filePath, std::vector<char*> appends)
{
	std::ofstream file(filePath, std::ios_base::app);

	if (file)
	{
		for (unsigned int i = 0; i < appends.size(); i++)
			file << appends[i];
	}
}
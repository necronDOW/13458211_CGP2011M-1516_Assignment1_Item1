#include "TextureManager.h"

TextureManager::TextureManager()
{

}

TextureManager::TextureManager(SDL_Instance &instance, char* path)
{
	this->path = path;
	this->instance = &instance;
}

TextureManager::~TextureManager()
{

}

void TextureManager::LoadTexture(char* fileName)
{
	std::string imgPath = std::string(path) + fileName + ".png";

	SDL_Surface* surface = IMG_Load(imgPath.c_str());
	if (surface == nullptr)
	{
		std::cout << "Surface could not be loaded correctly for image " << fileName << ".png." << std::endl;
		return;
	}

	Texture tmp = Texture(SDL_CreateTextureFromSurface(instance->GetRenderer(), surface));
	if (tmp.texture == nullptr)
	{
		std::cout << "Texture could not be loaded correctly from surface " << surface << "." << std::endl;
		return;
	}

	SDL_FreeSurface(surface);

	LoadTextureData(tmp, fileName);
	textures.push_back(tmp);
}

void TextureManager::LoadTextureData(Texture &tex, char* fileName)
{
	std::string imgPath = std::string(path) + fileName + ".data";

	std::ifstream file(imgPath);
	std::string buffer;

	if (!file)
		return;

	SDL_Rect bounds;
	bounds.x = 0;
	bounds.y = 0;
	SDL_QueryTexture(tex.texture, NULL, NULL, &bounds.w, &bounds.h);

	tex.ids.push_back("*");
	tex.data.push_back(bounds);

	int index = 1;
	while (std::getline(file, buffer))
	{
		if (buffer != "")
		{
			char* tmp;
			StrLib::str_copy((char*)buffer.c_str(), tmp);
			std::vector<char*> tmpArr = StrLib::str_split(tmp, " ");

			tex.ids.push_back("");
			tex.data.push_back(SDL_Rect());

			ParseData(tmpArr, tex.ids[index], tex.data[index]);
			index++;
		}
	}
}

void TextureManager::ParseData(std::vector<char*> &arr, char* &idTarget, SDL_Rect &dataTarget)
{
	if (arr.size() != 6)
		return;

	idTarget = arr[0];
	dataTarget = SDL_Rect();
	dataTarget.x = atoi(arr[2]);
	dataTarget.y = atoi(arr[3]);
	dataTarget.w = atoi(arr[4]);
	dataTarget.h = atoi(arr[5]);
}

SDL_Texture* &TextureManager::GetTexture(int index) { return textures[index].texture; }

bool TextureManager::GetSlice(int textureIndex, char* id, SDL_Texture* &outTexture, SDL_Rect* &outData)
{
	std::vector<char*> &ids = textures[textureIndex].ids;

	for (unsigned int i = 0; i < ids.size(); i++)
	{
		if (StrLib::str_contains(ids[i], id))
		{
			outTexture = textures[textureIndex].texture;
			outData = &textures[textureIndex].data[i];

			return true;
		}
	}

	return false;
}

bool TextureManager::GetSlice(int textureIndex, char* id, SDL_Texture* &outTexture, std::vector<SDL_Rect*> &outData, std::vector<char*> &outIDs)
{
	bool found = false;
	std::vector<char*> &ids = textures[textureIndex].ids;

	for (unsigned int i = 0; i < ids.size(); i++)
	{
		if (StrLib::str_contains(ids[i], id))
		{
			if (!found) outTexture = textures[textureIndex].texture;
			outData.push_back(&textures[textureIndex].data[i]);
			outIDs.push_back(ids[i]);

			found = true;
		}
	}
	
	if (found)
		return true;

	return false;
}
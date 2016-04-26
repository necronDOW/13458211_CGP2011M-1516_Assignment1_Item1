#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "SDL_Instance.h"
#include "StrLib.h"

#include <SDL_image.h>

class TextureManager
{
	struct Texture {
		SDL_Texture* texture;
		std::vector<char*> ids;
		std::vector<SDL_Rect> data;

		Texture(SDL_Texture* tex) 
			: texture(tex) { }
	};

	public:
		TextureManager();
		TextureManager(SDL_Instance &instance, char* path);
		~TextureManager();

		void LoadTexture(char* fileName);

		SDL_Texture* &GetTexture(int index);
		bool GetSlice(int textureIndex, char* id, SDL_Texture* &outTexture, SDL_Rect* &outData);
		bool GetSlice(int textureIndex, char* id, SDL_Texture* &outTexture, std::vector<SDL_Rect*> &outData, std::vector<char*> &outIDs);

	private:
		void LoadTextureData(Texture &tex, char* fileName);
		void ParseData(std::vector<char*> &arr, char* &idTarget, SDL_Rect &dataTarget);

		char* path;
		std::vector<Texture> textures;
		SDL_Instance* instance;
};

#endif
#include "AudioManager.h"
#include "Game.h"

AudioManager::AudioManager(Game* game)
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Failed to Initialize SDL_mixer." << std::endl;
		return;
	}
}

AudioManager::~AudioManager()
{

}

void AudioManager::Update()
{

}

void AudioManager::LoadMusic(char* fileName)
{
	music = Mix_LoadMUS(fileName);
	Mix_PlayMusic(music, -1);
}

void AudioManager::LoadClip(char* id, char* fileName)
{
	if (Mix_LoadWAV(fileName))
		clips.push_back(AudioClip(id, fileName));
}

void AudioManager::PlayClip(char* id)
{
	for (int i = 0; i < clips.size(); i++)
	{
		if (StringHelper::str_contains(clips[i].id, id))
		{
			Mix_PlayChannel(0, clips[i].clip, 0);
			return;
		}
	}
}

void AudioManager::PlayMusic()
{
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() == 1)
		Mix_PauseMusic();
}

void AudioManager::CleanUp()
{
	Mix_FreeMusic(music);

	for (int i = 0; i < clips.size(); i++)
	{
		Mix_FreeChunk(clips[i].clip);
		clips.erase(clips.begin() + i);
	}

	Mix_CloseAudio();
}
#include "AudioManager.h"

// Project includes
#include "Game.h"

AudioManager::AudioManager(Game* game)
{
	// Initialize SDL_mixer using Mix_OpenAudio, report success or failure.
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Failed to Initialize SDL_mixer.\n" << std::endl;
		return;
	}

	std::cout << "Audio Manager successfully Initialized.\n" << std::endl;
}

AudioManager::~AudioManager()
{

}

void AudioManager::LoadMusic(char* fileName)
{
	// Open music from file at given location.
	music = Mix_LoadMUS(fileName);
	Mix_PlayMusic(music, -1);
}

void AudioManager::LoadClip(char* id, char* fileName)
{
	// Load a WAV format clip from the given file location and add it to the clip vector.
	if (Mix_LoadWAV(fileName))
		clips.push_back(AudioClip(id, fileName));
}

void AudioManager::PlayClip(char* id)
{
	// Identify the desired clip from the clips vector and play if found.
	for (unsigned int i = 0; i < clips.size(); i++)
	{
		if (StrLib::str_contains(clips[i].id, id))
		{
			Mix_PlayChannel(0, clips[i].clip, 0);
			return;
		}
	}
}

void AudioManager::PlayMusic()
{
	// Play the music if it is already paused.
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
}

void AudioManager::PauseMusic()
{
	// Pause music if it is playing.
	if (Mix_PlayingMusic() == 1)
		Mix_PauseMusic();
}

void AudioManager::CleanUp()
{
	// Free the Mix_Music variable.
	Mix_FreeMusic(music);

	// Free all audio clips.
	for (unsigned int i = 0; i < clips.size(); i++)
	{
		Mix_FreeChunk(clips[i].clip);
		clips.erase(clips.begin() + i);
	}

	// Close SDL_mixer.
	Mix_CloseAudio();
}
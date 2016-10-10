#include "AudioManager.h"

// Project includes
#include "Game.h"
#include "Sprite.h"
#include "Text.h"
#include "Client.h"
#include "SceneManager.h"

AudioManager::AudioManager(Game* game, glm::vec2 position)
{
	this->game = game;

	// Initialize SDL_mixer using Mix_OpenAudio, report success or failure.
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Failed to Initialize SDL_mixer.\n" << std::endl;
		return;
	}

	std::cout << "Audio Manager successfully Initialized.\n" << std::endl;

	clipVolume = MIX_MAX_VOLUME / 2;
	musicVolume = MIX_MAX_VOLUME / 2;

	std::vector<char*> volumeCaptions = { "Effects Volume (PgUp/PgDn)" , "Music Volume (Home/End)" };

	for (unsigned int i = 0; i < volumeCaptions.size(); i++)
	{
		glm::vec2 tmpPos = position + glm::vec2(0, i * 20);

		barLabels.push_back(new Text(game, tmpPos, 14, volumeCaptions[i], 0, 0, 0));
		barSprites.push_back(new Sprite(game, tmpPos, 1.0f, "volumeBar"));
		ChangeVolume(0, i);
	}

	showVolume = false;
	timer = Timer(3.0f);
}

AudioManager::~AudioManager()
{

}

void AudioManager::HandleInput(SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_PAGEDOWN:
				ChangeVolume(-1, 0);
				break;
			case SDLK_PAGEUP:
				ChangeVolume(1, 0);
				break;
			case SDLK_END:
				ChangeVolume(-1, 1);
				break;
			case SDLK_HOME:
				ChangeVolume(1, 1);
				break;
			case SDLK_PAUSE:
				if (!event.key.repeat)
					ToggleMusic();
				break;
		}
	}
}

void AudioManager::Update()
{
	for (unsigned int i = 0; i < barSprites.size(); i++)
		barSprites[i]->Update();
}

void AudioManager::Render()
{
	if (showVolume)
	{
		for (unsigned int i = 0; i < barSprites.size(); i++)
			barSprites[i]->Render();

		for (unsigned int i = 0; i < barLabels.size(); i++)
			barLabels[i]->Render();

		if (timer.IsDone())
			showVolume = false;
	}
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

void AudioManager::SetLoopClip(char* id)
{
	if (loopClip == nullptr || StrLib::str_contains(loopClip->id, id))
	{
		for (unsigned int i = 0; i < clips.size(); i++)
		{
			if (StrLib::str_contains(clips[i].id, id))
			{
				loopClip = &clips[i];
				break;
			}
		}
	}

	Mix_PlayChannel(1, loopClip->clip, -1);
	ToggleLoopClip();
}

void AudioManager::ToggleLoopClip()
{
	if (loopClip != nullptr)
	{
		if (loopClip->clip->volume == 0)
			loopClip->clip->volume = clipVolume;
		else loopClip->clip->volume = 0;
	}
}

void AudioManager::ToggleMusic()
{
	// Alternate between paused and playing.
	if (Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else if (Mix_PlayingMusic() == 1)
		Mix_PauseMusic();
}


void AudioManager::ChangeVolume(int influence, int index)
{
	int volumeSelected = index == 0 ? clipVolume : musicVolume;
	volumeSelected += ((MIX_MAX_VOLUME / 16) * influence);

	if (volumeSelected > MIX_MAX_VOLUME) volumeSelected = MIX_MAX_VOLUME;
	else if (volumeSelected < 0) volumeSelected = 0;

	if (index == 0)
	{
		Mix_Volume(0, volumeSelected);
		Mix_Volume(1, volumeSelected);
		clipVolume = volumeSelected;
	}
	else
	{
		Mix_VolumeMusic(volumeSelected);
		musicVolume = volumeSelected;
	}

	showVolume = true;
	barSprites[index]->SetScale(barLabels[index]->GetDimensions().x + (volumeSelected * 2), barLabels[index]->GetDimensions().y);
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
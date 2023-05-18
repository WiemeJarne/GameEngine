#include "SDLSoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace dae;

class SDLSoundSystem::SDLSoundSystemImpl final
{
public:
	SDLSoundSystemImpl()
	{
		//initalize SDL audio system
		if (SDL_Init(SDL_INIT_AUDIO) == -1)
			std::cout << "failed to initialize SLD audio system: " << SDL_GetError() << '\n';

		//initialize SDL_mixer
		if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
			std::cout << "failed to open audio device: " << Mix_GetError() << '\n';

		//create and start the sound thread
		m_SoundThread = std::jthread{ [&] { SoundThread(); } };
	}

	~SDLSoundSystemImpl()
	{
		for (auto& sound : m_Sounds)
		{
			Mix_FreeChunk(sound);
		}

		m_Continue = false;
		m_SoundQueueCondition.notify_all();

		Mix_CloseAudio();
	}

	void SoundThread()
	{
		while (m_Continue)
		{
			std::unique_lock lock(m_SoundMutex);
			m_SoundQueueCondition.wait(lock);

			while (m_Continue && !m_SoundQueue.empty())
			{
				auto& sound{ m_SoundQueue.front() };
				Play(sound.first, sound.second);
				m_SoundQueue.pop();
			}
		}
	}

	void AddSound(const std::string& path)
	{
		Mix_Chunk* pChunk{ Mix_LoadWAV(path.c_str()) };

		if (pChunk)
			m_Sounds.push_back(pChunk);
	}

	void AddSoundToQueue(const soundId soundId, const int volume)
	{
		const std::lock_guard lock{ m_SoundMutex };
		m_SoundQueue.push({ soundId, volume });
		m_SoundQueueCondition.notify_all();
	}

	void Play(const soundId soundId, const int volume)
	{
		if (static_cast<int>(soundId) > m_Sounds.size())
		{
			std::cout << "invalid soundId\n";
			return;
		}

		int toUseVolume{};
		if (volume > MIX_MAX_VOLUME)
			toUseVolume = MIX_MAX_VOLUME;
		else if (volume < 0)
			toUseVolume = 0;
		else toUseVolume = volume;

		Mix_Volume(-1, toUseVolume);
		Mix_PlayChannel(-1, m_Sounds[soundId], 0);
	}

private:
	std::vector<Mix_Chunk*> m_Sounds{};
	std::queue<std::pair<const soundId, const int>> m_SoundQueue;
	std::jthread m_SoundThread{};
	std::mutex m_SoundMutex{};
	std::condition_variable m_SoundQueueCondition{};
	std::atomic<bool> m_Continue{ true };
};

SDLSoundSystem::SDLSoundSystem()
	: m_pImpl{ std::make_unique<SDLSoundSystemImpl>() }
{}

void SDLSoundSystem::AddSound(const std::string& path)
{
	m_pImpl->AddSound(path);
}

void SDLSoundSystem::Play(const soundId soundId, const int volume)
{
	m_pImpl->AddSoundToQueue(soundId, volume);
}
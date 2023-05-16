#pragma once
#include "SoundServiceLocator.h"
#include <memory>

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();

		void AddSound(const std::string& path) override;
		void Play(const soundId soundId, const int volume) override;

	private:
		class SDLSoundSystemImpl;

		std::unique_ptr<SDLSoundSystemImpl> m_pImpl;
	};
}
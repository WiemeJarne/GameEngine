#pragma once
#include <string>

namespace dae
{
	using soundId = unsigned short;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void AddSound(const std::string& path) = 0;
		virtual void Play(soundId soundId, const int volume) = 0;
	};

	class DefaultSoundSystem final : public SoundSystem
	{
	public:
		void AddSound(const std::string&) override {}
		void Play(soundId , const int ) override {}
	};

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *m_spSoundSystem; }
		static void registerSoundSystem(SoundSystem* pSoundSystem) { m_spSoundSystem = pSoundSystem; }

	private:
		static SoundSystem* m_spSoundSystem;
	};
}
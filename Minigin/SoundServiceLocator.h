#pragma once
#include <string>

namespace dae
{
	using soundId = unsigned short;

	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(const std::string& path, const int volume, bool loop = false) = 0;
	};

	class DefaultSoundSystem final : public SoundSystem
	{
	public:
		void Play(const std::string&, const int, bool) override {}
	};

	class ServiceLocator final
	{
	public:
		~ServiceLocator()
		{
			delete m_spSoundSystem;
		}

		static SoundSystem& GetSoundSystem() { return *m_spSoundSystem; }
		static void registerSoundSystem(SoundSystem* pSoundSystem) { m_spSoundSystem = pSoundSystem; }

	private:
		static SoundSystem* m_spSoundSystem;
	};
}
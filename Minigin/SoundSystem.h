#pragma once
using soundId = unsigned short;

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;
	virtual void Play(soundId soundId, const float volume) = 0;
};

class ServiceLocator final
{
public:
	static SoundSystem& GetSoundSystem() { return *m_spSoundSystem; }
	static void registerSoundSystem(SoundSystem* pSoundSystem) { m_spSoundSystem = pSoundSystem; }

private:
	static SoundSystem* m_spSoundSystem;
};
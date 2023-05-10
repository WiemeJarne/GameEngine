#pragma once
#include "SoundSystem.h"

class SDLSoundSystem : public SoundSystem
{
public:
	void Play(const soundId soundId, const float volume) override;
};


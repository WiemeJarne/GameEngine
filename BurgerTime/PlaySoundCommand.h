#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"

namespace commands
{
	class PlaySoundCommand final : public dae::Command
	{
	public:
		PlaySoundCommand(dae::SoundSystem* pSoundSystem);
		~PlaySoundCommand();

		void Execute() override;

	private:
		dae::SoundSystem* m_pSoundSystem;
	};
}
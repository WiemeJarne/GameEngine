#pragma once
#include "Command.h"
#include "SoundServiceLocator.h"

namespace commands
{
	class PlaySoundCommand final : public Command
	{
	public:
		PlaySoundCommand(dae::SoundSystem* pSoundSystem);
		~PlaySoundCommand();

		void Execute() override;

	private:
		dae::SoundSystem* m_pSoundSystem;
	};
}
#include "PlaySoundCommand.h"

using namespace commands;

PlaySoundCommand::PlaySoundCommand(dae::SoundSystem* pSoundSystem)
	: m_pSoundSystem{ pSoundSystem }
{
	dae::ServiceLocator::registerSoundSystem(pSoundSystem);
}

PlaySoundCommand::~PlaySoundCommand()
{
	delete m_pSoundSystem;
}

void PlaySoundCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem().Play(0u, 25);
}
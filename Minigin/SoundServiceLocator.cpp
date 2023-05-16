#include "SoundServiceLocator.h"

dae::SoundSystem* dae::ServiceLocator::m_spSoundSystem{ new dae::DefaultSoundSystem() };
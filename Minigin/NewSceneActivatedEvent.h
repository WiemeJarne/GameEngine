#pragma once
#include "BaseEvent.h"
#include "Scene.h"

namespace dae
{
	class NewSceneActivatedEvent : public BaseEvent
	{
	public:
		NewSceneActivatedEvent(Scene* pNewScene)
			: m_pNewlyActivatedScene { pNewScene }
		{}

		Scene* GetNewlyActivatedScene() const { return m_pNewlyActivatedScene; }

	private:
		Scene* m_pNewlyActivatedScene;
	};
}

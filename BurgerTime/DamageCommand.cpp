#include "DamageCommand.h"

namespace commands
{
	DamageCommand::DamageCommand(dae::GameObject* go, int amountOfDamage)
		: m_AmountOfDamage{ amountOfDamage }
	{
		m_HealthComponent = go->GetComponent<HealthComponent>();
	}

	void DamageCommand::Execute()
	{
		if(m_HealthComponent)
			m_HealthComponent->Damage(m_AmountOfDamage);
	}
}
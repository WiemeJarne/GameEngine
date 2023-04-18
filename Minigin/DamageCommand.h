#pragma once
#include "Command.h"
#include "HealthComponent.h"

namespace commands
{
	class DamageCommand : public Command
	{
	public:
		DamageCommand(dae::GameObject* go, int amountOfDamage);

		virtual ~DamageCommand() = default;
		DamageCommand(const DamageCommand&) = delete;
		DamageCommand(DamageCommand&&) = delete;
		DamageCommand& operator=(const DamageCommand&) = delete;
		DamageCommand& operator=(DamageCommand&&) = delete;

		void Execute() override;

	private:
		HealthComponent* m_HealthComponent;
		const int m_AmountOfDamage;
	};
}
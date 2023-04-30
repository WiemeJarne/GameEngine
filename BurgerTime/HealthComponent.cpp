#include "HealthComponent.h"
#include "Events.h"

HealthComponent::HealthComponent(dae::GameObject* owner, int amountOfLives)
	: Component(owner)
	, m_AmountOfLives{ amountOfLives }
{}

void HealthComponent::Damage(int amount)
{
	m_AmountOfLives -= amount;

	if (m_AmountOfLives < 0)
		m_AmountOfLives = 0;

	Notify(this, static_cast<int>(Events::playerLostLife));
}
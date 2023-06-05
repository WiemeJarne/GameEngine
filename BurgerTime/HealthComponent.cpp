#include "HealthComponent.h"
#include "EngineEvents.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "BurgerPartComponent.h"
#include <iostream>

HealthComponent::HealthComponent(dae::GameObject* owner, int amountOfLives, bool isOwnerPlayer)
	: Component(owner)
	, m_AmountOfLives{ amountOfLives }
	, m_IsOwnerPlayer{ isOwnerPlayer }
{
	dae::EventQueue::GetInstance().AddListener(this);
}

HealthComponent::~HealthComponent()
{
	dae::EventQueue::GetInstance().RemoveListener(this);
}

void HealthComponent::Update()
{
	if (m_AmountOfLives <= 0)
	{
		m_SecSinceDeath += Timer::GetInstance().GetElapsedSec();			
	}
}

void HealthComponent::OnNotify(std::any data, int eventId, bool isEngineEvent)
{
	if (m_IsOwnerPlayer || !isEngineEvent || m_AmountOfLives == 0)
		return;

	if (eventId == static_cast<int>(dae::EngineEvents::collisionEvent))
	{
		auto collisionData{ std::any_cast<dae::CollidedGameObjects>(data) };

		if (collisionData.pTriggered != m_pOwner)
			return;

		auto burgerPartComponent{ collisionData.pOther->GetComponent<BurgerPartComponent>() };

		if (!burgerPartComponent)
			return;

		//check if the burgerPart is falling and if the player is below it
		if (burgerPartComponent->GetIsFalling() && burgerPartComponent->GetTopLeftPos().y < m_pOwner->GetLocalPos().y)
		{
			Damage(1);
		}
	}
}

void HealthComponent::Damage(int amount)
{
	if (m_AmountOfLives > 0)
	{
		m_AmountOfLives -= amount;

		if (m_AmountOfLives == 0)
		{
			m_SecSinceDeath = 0.f;
		}
	}
}

void HealthComponent::Heal(int amount)
{
	m_AmountOfLives += amount;
}

void HealthComponent::Reset()
{
	m_AmountOfLives = m_StartAmountOfLives;
	m_SecSinceDeath = 0.f;
}
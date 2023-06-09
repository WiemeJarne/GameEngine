#include "HealthComponent.h"
#include "EngineEvents.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "BurgerPartComponent.h"
#include "DamageComponent.h"
#include "TexturedGameObjectPrefab.h"
#include "Scene.h"
#include "Events.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "EnemyAIComponent.h"
#include <iostream>

HealthComponent::HealthComponent(dae::GameObject* owner, int amountOfLives, bool isPlayer)
	: Component(owner)
	, m_StartAmountOfLives{ amountOfLives }
	, m_AmountOfLives{ amountOfLives }
	, m_IsOwnerPlayer{ isPlayer }
{
	dae::EventQueue::GetInstance().AddListener(this);
}

HealthComponent::HealthComponent(dae::GameObject* owner, int amountOfLives, const glm::vec2& visualizationPos, const std::string& textureFilePath, bool isPlayer)
	: HealthComponent(owner, amountOfLives, isPlayer)
{
	VisualizeHealth(visualizationPos, textureFilePath);
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
	else m_SecSinceLiveLost += Timer::GetInstance().GetElapsedSec();
}

void HealthComponent::OnNotify(std::any data, int eventId, bool isEngineEvent)
{
	if (!isEngineEvent || m_AmountOfLives == 0)
		return;

	if (eventId == static_cast<int>(dae::EngineEvents::collisionEvent))
	{
		auto collisionData{ std::any_cast<dae::CollidedGameObjects>(data) };

		if (collisionData.pTriggered != m_pOwner)
			return;

		auto pBurgerPartComponent{ collisionData.pOther->GetComponent<BurgerPartComponent>() };

		if (!m_IsOwnerPlayer) //if this component's owner is not a player
		{
			//check if the pOther has a burgerPartComponent and check if the burgerPart is falling
			if (pBurgerPartComponent && pBurgerPartComponent->GetIsFalling())
			{
				//if the enemy is below it damage the enemy
				if (pBurgerPartComponent->GetTopLeftPos().y < m_pOwner->GetLocalPos().y)
					Damage(m_AmountOfLives);
				//if the enemy is not below the burgerPart set the owner of the enemy equal to the owner of the burgerPart
				else if (!pBurgerPartComponent->GetHasReachedPlate())
				{
					//get the EnemyAIComponent to get the height of the enemy and the burgerPart and check if the feet of the enemy are below the middle of the burgerPart
					if(pBurgerPartComponent->GetOwner()->GetLocalPos().y + pBurgerPartComponent->GetHeight() <= m_pOwner->GetLocalPos().y + m_pOwner->GetComponent<EnemyAIComponent>()->GetHeight() + 5.f)
						m_pOwner->SetParent(pBurgerPartComponent->GetOwner(), true);
				}
			}
		}
		else //if this component's owner is a player
		{
			//check if the otherComponent has a damage component if so the player takes damage
			auto pDamageComponent{ collisionData.pOther->GetComponent<DamageComponent>() };

			if (pDamageComponent)
			{
				Damage(pDamageComponent->GetDamageAmount());
			}
		}
	}
}

void HealthComponent::Damage(int amount, bool shouldBreadCastDieEvent)
{
	if (m_AmountOfLives > 0 && m_SecSinceLiveLost >= 1.f)
	{
		m_SecSinceLiveLost = 0.f;

		m_AmountOfLives -= amount;

		if(m_IsOwnerPlayer && shouldBreadCastDieEvent)
			dae::EventQueue::GetInstance().AddEvent(std::any(), static_cast<int>(Event::playerLostLife), false);

		if (m_pVisualizeGameObjects.size() > 0)
			m_pVisualizeGameObjects[m_AmountOfLives]->SetLocalPosition(0.f, -100.f);

		if (m_AmountOfLives == 0)
		{
			m_SecSinceDeath = 0.f;

			if (shouldBreadCastDieEvent)
			{
				if (m_IsOwnerPlayer)
					dae::EventQueue::GetInstance().AddEvent(std::any(), static_cast<int>(Event::playerDied), false);
				else dae::EventQueue::GetInstance().AddEvent(std::any(m_pOwner->GetComponent<dae::TextureComponent>()), static_cast<int>(Event::enemyDied), false);
			}
		}
	}
}

void HealthComponent::Reset()
{
	m_AmountOfLives = m_StartAmountOfLives;
	m_SecSinceDeath = 0.f;
}

void HealthComponent::VisualizeHealth(const glm::vec2& pos, const std::string& textureFilePath)
{
	if (m_pVisualizeGameObjects.size() > 0)
		return;

	dae::Scene* pScene{ dae::SceneManager::GetInstance().GetSceneByIndex(0) };

	if (!pScene)
		return;

	constexpr float spaceBetweenLives{ 20 };

	for (int index{}; index < m_AmountOfLives; ++index)
	{
		auto gameObject{ std::make_unique<TexturedGameObjectPrefab>(pScene, textureFilePath, glm::vec2(pos.x + index * spaceBetweenLives, pos.y))->GetGameObject() };
		m_pVisualizeGameObjects.push_back(gameObject.get());
		pScene->Add(std::move(gameObject));
	}
}

void HealthComponent::Die()
{
	m_AmountOfLives = 0;
}
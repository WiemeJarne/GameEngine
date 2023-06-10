#include "StunEnemyComponent.h"
#include "EngineEvents.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "DamageComponent.h"
#include "HealthComponent.h"
#include "Timer.h"

StunEnemyComponent::StunEnemyComponent(dae::GameObject* pOwner, float amountOfSecStunned, float amountOfSecAlive)
	: Component(pOwner)
	, m_AmountOfSecStunned{ amountOfSecStunned }
	, m_AmountOfSecAlive{ amountOfSecAlive }
{
	dae::EventQueue::GetInstance().AddListener(this);
}

StunEnemyComponent::~StunEnemyComponent()
{
	dae::EventQueue::GetInstance().RemoveListener(this);
}

void StunEnemyComponent::Update()
{
	m_AmountOfSecSinceSpawned += dae::Timer::GetInstance().GetElapsedSec();

	if(m_AmountOfSecSinceSpawned >= m_AmountOfSecAlive)
	{
		auto pScene{ dae::SceneManager::GetInstance().GetSceneByIndex(0) };

		if (pScene)
			pScene->QueueForRemove(m_pOwner);
	}
}

void StunEnemyComponent::OnNotify(std::any data, int eventId, bool isEngineEvent)
{
	if (!isEngineEvent || static_cast<dae::EngineEvents>(eventId) != dae::EngineEvents::collisionEvent)
		return;

	const auto collisionData{ std::any_cast<dae::CollidedGameObjects>(data) };

	//if the triggered object is not this object or the other object doesn't have a damageComponent (so it is not an enemy) return
	if (collisionData.pTriggered != GetOwner() || !collisionData.pOther->HasComponent<DamageComponent>())
		return;

	//get the healthComponent from other object
	const auto pHealthComponent{ collisionData.pOther->GetComponent<HealthComponent>() };

	//check if the other object is colliding with pepper
	if(pHealthComponent && !pHealthComponent->GetIsCollidingWithPepper())
	{
		pHealthComponent->SetIsCollidingWithPepper(true);
		pHealthComponent->SetAmountOfSecStunned(m_AmountOfSecStunned);
	}
}
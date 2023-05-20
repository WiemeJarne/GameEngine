#include "CollisionManager.h"
#include "EngineEvents.h"
#include <iostream>

void dae::CollisionManager::Update()
{
	if (!m_pEventQueue)
		m_pEventQueue = &EventQueue::GetInstance();

	//loop over all the collisionBoxComponents and check if they are colliding
	for (auto& pCollider : m_CollisionBoxComponents)
	{
		auto Collider1TopLeft{ pCollider->GetTopLeftPos() };
		auto collider1Width{ pCollider->GetWidth() };
		auto collider1Height{ pCollider->GetHeight() };

		for (auto& pOtherCollider : m_CollisionBoxComponents)
		{
			//make sure the components don't collide with themself
			if (pCollider == pOtherCollider)
				continue;

			if (AreColliding(Collider1TopLeft, collider1Width, collider1Height, pOtherCollider->GetTopLeftPos(), pOtherCollider->GetWidth(), pOtherCollider->GetHeight()))
			{
				m_pEventQueue->AddEvent(std::any(CollidedGameObjects(pCollider->GetOwner(), pOtherCollider->GetOwner())), static_cast<int>(EngineEvents::collisionEvent), true);
			}
		}
	}
}

void dae::CollisionManager::AddCollider(CollisionBoxComponent* pCollisionBoxComponent)
{
	m_CollisionBoxComponents.push_back(pCollisionBoxComponent);
}

void dae::CollisionManager::RemoveCollider(CollisionBoxComponent* pCollisionBoxComponent)
{
	if (!m_CollisionBoxComponents.empty())
	{
		m_CollisionBoxComponents.erase(std::remove_if(m_CollisionBoxComponents.begin(), m_CollisionBoxComponents.end()
		, [&](CollisionBoxComponent* pOtherCollisionBoxComponent) {return pCollisionBoxComponent == pOtherCollisionBoxComponent; }), m_CollisionBoxComponents.end());

	}
}

bool dae::CollisionManager::AreColliding(const glm::vec2& collider1TopLeft, float collider1With, float collider1Height, const glm::vec2& collider2TopLeft, float collider2Width, float collider2Height)
{
	//if one rectangle is to the left side of the other they are not overlapping
	if (collider1TopLeft.x >= (collider2TopLeft.x + collider2Width) || collider2TopLeft.x >= (collider1TopLeft.x + collider1With))
		return false;

	//if one rectangle is above the other they are not overlapping
	if ((collider1TopLeft.y + collider1Height) <= collider2TopLeft.y || (collider2TopLeft.y + collider2Height) <= collider1TopLeft.y)
		return false;

	return true;
}
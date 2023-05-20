#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "MoveComponent.h"
#include "Events.h"
#include "EventQueue.h"
#include "LevelGrid.h"
#include "EngineEvents.h"
#include "CollisionManager.h"
#include "BurgerPartComponent.h"
#include <iostream>

EnemyAIComponent::EnemyAIComponent(dae::GameObject* pOwner, float moveSpeed)
	: Component(pOwner)
{
	auto moveComponent{ std::make_unique<MoveComponent>(pOwner, moveSpeed, false) };
	m_pMoveComponent = moveComponent.get();
	pOwner->AddComponent(std::move(moveComponent));

	dae::EventQueue::GetInstance().AddListener(this);
}

void EnemyAIComponent::Update()
{
	//constexpr float epsilon{ 0.1f };

	//calculate the owner middlePos
	auto ownerMiddlePos{ m_pOwner->GetLocalPos() };
	ownerMiddlePos.x += 4.f;
	ownerMiddlePos.y += 8.f;

	glm::vec2 upDirection{ 0.f, -1.f };
	glm::vec2 downDirection{ 0.f, 1.f };
	glm::vec2 leftDirection{ -1.f, 0.f };
	glm::vec2 rightDirection{ 1.f, 0.f };

	//get the cell the player is in
	auto pPlayerCell{ LevelGrid::GetInstance().GetCell(m_PlayerMiddlePos) };

	if (!pPlayerCell)
		return;
	
	//get the cell where this enemy is in
	auto pEnemyCell{ LevelGrid::GetInstance().GetCell(ownerMiddlePos) };

	if (!pEnemyCell)
	{
		m_pMoveComponent->Move(m_PreviousDirection);
		return;
	}

	//check if the shortest way to the player is up or down
	if ((abs(abs(m_PlayerMiddlePos.y) - abs(ownerMiddlePos.y)) < abs(abs(m_PlayerMiddlePos.x) - abs(ownerMiddlePos.x))
		|| pPlayerCell->rowNr != pEnemyCell->rowNr) && pPlayerCell->collNr == pEnemyCell->collNr)
	{
		//check if the player is above this enemy
		if (m_PlayerMiddlePos.y < ownerMiddlePos.y)
		{
			//if so try to move up and return when succeeded
			if (m_pMoveComponent->Move(upDirection))
			{
				m_PreviousDirection = upDirection;
				return;
			}
		}
		//if moving up fails try to move down
		if (m_pMoveComponent->Move(downDirection))
		{
			m_PreviousDirection = downDirection;
			return;
		}
	}
	else if(m_PlayerMiddlePos.x < ownerMiddlePos.x) //if the player is not above or below this enemy check if the player is to the left of this enemy
	{
		//if so try to move to the left and return when succeeded
		if (m_pMoveComponent->Move(leftDirection))
		{
			m_PreviousDirection = leftDirection;
			return;
		}

		//check if the player is above this enemy
		if (m_PlayerMiddlePos.y < ownerMiddlePos.y)
		{
			//if so try to move up and return when succeeded
			if (m_pMoveComponent->Move(upDirection))
			{
				m_PreviousDirection = upDirection;
				return;
			}
		}
		//if moving up fails try to move down
		if (m_pMoveComponent->Move(downDirection))
		{
			m_PreviousDirection = downDirection;
			return;
		}
	}

	//if moving to the left fails try to move to the right
	if (m_pMoveComponent->Move(rightDirection))
	{
		m_PreviousDirection = rightDirection;
		return;
	}

	//check if the player is above this enemy
	if (m_PlayerMiddlePos.y < ownerMiddlePos.y)
	{
		//if so try to move up and return when succeeded
		if (m_pMoveComponent->Move(upDirection))
		{
			m_PreviousDirection = upDirection;
			return;
		}
	}
	//if moving up fails try to move down
	if (m_pMoveComponent->Move(downDirection))
	{
		m_PreviousDirection = downDirection;
		return;
	}
}

void EnemyAIComponent::OnNotify(std::any data, int eventId, bool isEngineEvent)
{
	if (isEngineEvent)
		return;

	if (eventId == static_cast<int>(Event::playerMoved))
		m_PlayerMiddlePos = std::any_cast<glm::vec2>(data);
}
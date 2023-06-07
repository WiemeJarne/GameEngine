#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "MoveComponent.h"
#include "Events.h"
#include "EventQueue.h"
#include "LevelManager.h"
#include "EngineEvents.h"
#include "CollisionManager.h"
#include "BurgerPartComponent.h"
#include <iostream>
#include <glm/glm.hpp>

EnemyAIComponent::EnemyAIComponent(dae::GameObject* pOwner, float moveSpeed)
	: Component(pOwner)
{
	auto moveComponent{ std::make_unique<MoveComponent>(pOwner, moveSpeed, false) };
	m_pMoveComponent = moveComponent.get();
	pOwner->AddComponent(std::move(moveComponent));

	dae::EventQueue::GetInstance().AddListener(this);
}

EnemyAIComponent::~EnemyAIComponent()
{
	dae::EventQueue::GetInstance().RemoveListener(this);
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

	//get the active grid
	auto pActiveGrid{ LevelManager::GetInstance().GetActiveLevelGrid() };

	//get the cell the player is in
	auto pPlayerCell{ pActiveGrid->GetCell(m_PlayerMiddlePos) };

	if (!pPlayerCell)
		return;
	
	//get the cell where this enemy is in
	auto pEnemyCell{ pActiveGrid->GetCell(ownerMiddlePos) };

	const float distanceToPlayer{ glm::length(m_PlayerMiddlePos - ownerMiddlePos) };

	//check if this enemy is on a ladder
	if (pEnemyCell && pEnemyCell->cellKind == CellKind::ladder && m_pClosestLadder != m_pPreviousClimbedLadder)
	{
		m_pClosestLadder = nullptr;
		m_pPreviousClimbedLadder = pEnemyCell;

		//if the previous direction was going up try going up
		if (m_PreviousDirection == upDirection && m_pMoveComponent->Move(upDirection))
			return;

		//if the previous direction was going down try going down
		if (m_PreviousDirection == downDirection && m_pMoveComponent->Move(downDirection))
			return;

		//if the previous direction was not up or down check if the player is above the enemy if so try to move up
		if (ownerMiddlePos.y > m_PlayerMiddlePos.y && m_pMoveComponent->Move(upDirection))
		{
			m_PreviousDirection = upDirection;
			return;
		}
		else if (m_pMoveComponent->Move(downDirection))
		{
			m_PreviousDirection = downDirection;
			return;
		}
	}

	//get the closest ladder cell if this enemy is not already walking to one
	if(!m_pClosestLadder)
		m_pClosestLadder = pActiveGrid->GetNearestCellOfKind(ownerMiddlePos, CellKind::ladder);

	//calculate the distance to the ladder
	const float distanceToLadder{ glm::length(m_pClosestLadder->middlePos - ownerMiddlePos) };

	//calculate the distance from the ladder to the player
	const float distanceFromLadderToPlayer{ glm::length(m_PlayerMiddlePos - m_pClosestLadder->middlePos) };

	glm::vec2 toMovePos{};

	//check if the ladder is closer then the player and if it brings this enemy closer to the player
	if (distanceToLadder < distanceToPlayer && distanceFromLadderToPlayer < distanceToPlayer)
		toMovePos = m_pClosestLadder->middlePos; //if so move to the ladder
	else toMovePos = m_PlayerMiddlePos; //else move to the player


	

	//if this enemy is not in the same row then the player
	if (pEnemyCell && pEnemyCell->rowNr != pPlayerCell->rowNr)
	{
		////if the previous direction was going to the left try going to the left
		if (m_PreviousDirection == upDirection && m_pMoveComponent->Move(upDirection))
			return;

		//if the previous direction was going to the right try going to the right
		if (m_PreviousDirection == downDirection && m_pMoveComponent->Move(downDirection))
			return;

		//check if the ladder is to the left of this enemy if so try to move to the left
		if (toMovePos.y < ownerMiddlePos.y && m_pMoveComponent->Move(upDirection))
		{
			m_PreviousDirection = upDirection;
			return;
		}
		else if (m_pMoveComponent->Move(downDirection)) //otherwise try to move to the right
		{
			m_PreviousDirection = downDirection;
			return;
		}
	}

	//if the previous direction was going to the left try going to the left
	if (m_PreviousDirection == leftDirection && m_pMoveComponent->Move(leftDirection))
		return;

	//if the previous direction was going to the right try going to the right
	if (m_PreviousDirection == rightDirection && m_pMoveComponent->Move(rightDirection))
		return;

	//check if the ladder is to the left of this enemy if so try to move to the left
	if (toMovePos.x < ownerMiddlePos.x && m_pMoveComponent->Move(leftDirection))
	{
		m_PreviousDirection = leftDirection;
		return;
	}
	else if (m_pMoveComponent->Move(rightDirection)) //otherwise try to move to the right
	{
		m_PreviousDirection = rightDirection;
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
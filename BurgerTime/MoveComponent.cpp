#include "MoveComponent.h"
#include "Timer.h"
#include "GameObject.h"
#include "Events.h"
#include <iostream>

MoveComponent::MoveComponent(dae::GameObject* owner, float moveSpeed)
	: Component(owner)
	, m_MoveSpeed{ moveSpeed }
{}

void MoveComponent::Move(const glm::vec2& moveDirection)
{
	const float epsilon{ 0.5f };

	auto ownerLocalPos{ m_pOwner->GetLocalPos() };

	bool canMove{};

	//calculate middlePos of the gameObject
	auto ownerMiddlePos{ ownerLocalPos };
	ownerMiddlePos.x += 8.f;
	ownerMiddlePos.y += 8.f;

	//get the cell the gameObject is in
	auto pCell = LevelGrid::GetInstance().GetCell(ownerMiddlePos);

	if (!pCell)
	{
		canMove = true;
	}

	if (pCell != m_pPreviousCell)
	{
		m_pPreviousCell = pCell;
		m_HasSnappedToPlatform = false;
	}
		
	//const float cellSideLenght{ LevelGrid::GetInstance().GetCellSideLenght() };

	//if gameObject is on a shortFloor or longFloor or shorGoDown or longGoDown align his feet with the platform
	switch (pCell->cellKind)
	{
	case CellKind::shortFloor:
	case CellKind::longFloor:
	case CellKind::shortGoDown:
	case CellKind::longGoDown:
		if (!m_HasSnappedToPlatform)
		{
			m_HasSnappedToPlatform = true;
			m_pOwner->SetLocalPosition(ownerLocalPos.x, pCell->middlePos.y - 8.f);
		}		
		break;
	}

	//if gameObject wants to move to up
	if (abs(moveDirection.x) < epsilon && abs(moveDirection.y + 1.f) < epsilon)
	{
		//if the cell the gameOjbect is in is a shorGoDown or a longGoDown then he can move until his feet aling with the platform
		switch (pCell->cellKind)
		{
		case CellKind::shortGoDown:
		case CellKind::longGoDown:
			if (ownerMiddlePos.y > pCell->middlePos.y)
			{
				canMove = true;
			}
			break;

		case CellKind::shortGoUp:
		case CellKind::shortGoUpAndDown:
		case CellKind::ladder:
			canMove = true;
			break;

		//if the cell the gameObject is in is a longGoUp or longGoUpAndDown make sure the middle of the middle gameObject is above the ladder so only check x
		case CellKind::longGoUp:
		case CellKind::longGoUpAndDown:
			if (ownerMiddlePos.x >= pCell->middlePos.x - cellSideLenght / 2.f && ownerMiddlePos.x <= pCell->middlePos.x + cellSideLenght / 2.f)
				canMove = true;
			break;
		}
	}

	//if gameObject wants to move down
	if (abs(moveDirection.x) < epsilon && abs(moveDirection.y - 1.f) < epsilon)
	{
		//if the cell the gameOjbect is in is a shorGoUp or a longGoUp then he can move until his feet aling with the platform
		switch (pCell->cellKind)
		{
		case CellKind::shortGoUp:
		case CellKind::longGoUp:
			if (ownerMiddlePos.y < pCell->middlePos.y)
			{
				canMove = true;
			}
			break;

		case CellKind::shortGoDown:
		case CellKind::shortGoUpAndDown:
		case CellKind::ladder:
			canMove = true;
			break;

		//if the cell the gameObject is in is a longGoDown or longGoUpAndDown make sure the middle of the middle gameObject is above the ladder so only check x
		case CellKind::longGoDown:
		case CellKind::longGoUpAndDown:
			if (ownerMiddlePos.x >= pCell->middlePos.x - cellSideLenght / 2.f && ownerMiddlePos.x <= pCell->middlePos.x + cellSideLenght / 2.f)
				canMove = true;
			break;
		}
	}

	//if gameObject wants to move to the left
	if (abs(moveDirection.x + 1.f) < epsilon && abs(moveDirection.y) < epsilon)
	{
		//if the gameOjbect is on any type of floor or goUp/goDown/goUpAndDown and the left neighbor exist then when the left neighbor is not an shortEmpty or a longEmpty cell he can move to the left
		//when the left neighbor is a shortEmpty or longEmpty or there is none then he can move until his left side aligns with the left side of the cell
		switch (pCell->cellKind)
		{
		case CellKind::longFloor:
		case CellKind::shortFloor:
		case CellKind::shortGoUp:
		case CellKind::shortGoDown:
		case CellKind::shortGoUpAndDown:
		case CellKind::longGoUp:
		case CellKind::longGoDown:
		case CellKind::longGoUpAndDown:
			if ((!pCell->pLeftNeighbor || pCell->pLeftNeighbor->cellKind == CellKind::shortEmpty
				|| pCell->pLeftNeighbor->cellKind == CellKind::longEmpty) && ownerMiddlePos.x < pCell->middlePos.x)
			{
				canMove = false;
			}
			else
			{
				canMove = true;
			}
			break;
		}

	}

	//if gameObject wants to move to the right
	if (abs(moveDirection.x - 1.f) < epsilon && abs(moveDirection.y) < epsilon)
	{
		//if the gameOjbect is on any type of floor or goUp/goDown/goUpAndDown and the right neighbor exist then when the right neighbor is not an shortEmpty or a longEmpty cell he can move to the right
		//when the right neighbor is a shortEmpty or longEmpty or there is none then he can move until his right side aligns with the left side of the cell
		switch (pCell->cellKind)
		{
		case CellKind::longFloor:
		case CellKind::shortFloor:
		case CellKind::shortGoUp:
		case CellKind::shortGoDown:
		case CellKind::shortGoUpAndDown:
		case CellKind::longGoUp:
		case CellKind::longGoDown:
		case CellKind::longGoUpAndDown:
			if ((!pCell->pRightNeighbor || pCell->pRightNeighbor->cellKind == CellKind::shortEmpty
				|| pCell->pRightNeighbor->cellKind == CellKind::longEmpty) && ownerMiddlePos.x > pCell->middlePos.x)
			{
				canMove = false;
			}
			else
			{
				canMove = true;
			}
			break;
		}
	}

	if (canMove)
	{
		m_pOwner->SetLocalPosition(m_pOwner->GetLocalPos().x + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * moveDirection.x,
			m_pOwner->GetLocalPos().y + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * moveDirection.y);

		Notify(m_pOwner, static_cast<int>(Events::gameObjectMoved));
	}
}
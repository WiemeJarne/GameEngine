#include "MoveComponent.h"
#include "Timer.h"
#include "GameObject.h"
#include "Events.h"
#include "EventQueue.h"
#include "RenderComponent.h"

MoveComponent::MoveComponent(dae::GameObject* owner, float moveSpeed, bool isPlayer)
	: Component(owner)
	, m_MoveSpeed{ moveSpeed }
	, m_IsPlayer{ isPlayer }
{
	if (owner->HasComponent<RenderComponent>())
	{
		const auto ownerSize{ owner->GetComponent<RenderComponent>()->GetTextureComponent()->GetSize() };
		m_OwnerWidth = static_cast<float>(ownerSize.x);
		m_OwnerHeight = static_cast<float>(ownerSize.y);
	}
}

bool MoveComponent::Move(const glm::vec2& moveDirection)
{
	const float epsilon{ 0.5f };

	auto ownerLocalPos{ m_pOwner->GetLocalPos() };

	bool canMove{};

	//calculate middlePos of the gameObject
	auto ownerMiddlePos{ ownerLocalPos };
	ownerMiddlePos.x += m_OwnerWidth / 2.f;
	ownerMiddlePos.y += m_OwnerHeight / 2.f;

	//get the cell the gameObject is in
	auto pCell = LevelGrid::GetInstance().GetCell(ownerMiddlePos);

	const float cellSideLenght{ LevelGrid::GetInstance().GetCellSideLenght() };

	if (!pCell)
	{
		Move(m_pOwner->GetLocalPos().x + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * moveDirection.x,
			m_pOwner->GetLocalPos().y + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * moveDirection.y);

		if (m_IsPlayer)
		{
			dae::EventQueue::GetInstance().AddEvent(std::any(ownerMiddlePos), static_cast<int>(Event::playerMoved), false);
		}

		return true;
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
		canMove = CanMoveUp(pCell, ownerMiddlePos, cellSideLenght);
	}

	//if gameObject wants to move down
	if (abs(moveDirection.x) < epsilon && abs(moveDirection.y - 1.f) < epsilon)
	{
		canMove = CanMoveDown(pCell, ownerMiddlePos, cellSideLenght);
	}

	//if gameObject wants to move to the left
	if (abs(moveDirection.x + 1.f) < epsilon && abs(moveDirection.y) < epsilon)
	{
		canMove = CanMoveLeft(pCell, ownerMiddlePos);
	}

	//if gameObject wants to move to the right
	if (abs(moveDirection.x - 1.f) < epsilon && abs(moveDirection.y) < epsilon)
	{
		canMove = CanMoveRight(pCell, ownerMiddlePos);
	}

	if (canMove)
	{
		Move(m_pOwner->GetLocalPos().x + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * moveDirection.x,
			m_pOwner->GetLocalPos().y + Timer::GetInstance().GetElapsedSec() * m_MoveSpeed * moveDirection.y);

		if (m_IsPlayer)
		{
			dae::EventQueue::GetInstance().AddEvent(std::any(ownerMiddlePos), static_cast<int>(Event::playerMoved), false);
		}
	}

	return canMove;
}

bool MoveComponent::CanMoveUp(Cell* pCell, const glm::vec2& ownerMiddlePos, float cellSideLenght)
{
	//if the cell the gameOjbect is in is a shorGoDown or a longGoDown then he can move until his feet aling with the platform
	switch (pCell->cellKind)
	{
	case CellKind::shortGoDown:
	case CellKind::longGoDown:
		if (ownerMiddlePos.y > pCell->middlePos.y)
		{
			return true;
		}
		break;

	case CellKind::shortGoUp:
	case CellKind::shortGoUpAndDown:
	case CellKind::ladder:
		return true;
		break;

		//if the cell the gameObject is in is a longGoUp or longGoUpAndDown make sure the middle of the middle gameObject is above the ladder so only check x
	case CellKind::longGoUp:
	case CellKind::longGoUpAndDown:
		if (ownerMiddlePos.x >= pCell->middlePos.x - cellSideLenght / 2.f && ownerMiddlePos.x <= pCell->middlePos.x + cellSideLenght / 2.f)
			return true;
		break;
	}

	return false;
}

bool MoveComponent::CanMoveDown(Cell* pCell, const glm::vec2& ownerMiddlePos, float cellSideLenght)
{
	//if the cell the gameOjbect is in is a shorGoUp or a longGoUp then he can move until his feet aling with the platform
	switch (pCell->cellKind)
	{
	case CellKind::shortGoUp:
	case CellKind::longGoUp:
		if (ownerMiddlePos.y < pCell->middlePos.y)
		{
			return true;
		}
		break;

	case CellKind::shortGoDown:
	case CellKind::shortGoUpAndDown:
	case CellKind::ladder:
		return true;
		break;

		//if the cell the gameObject is in is a longGoDown or longGoUpAndDown make sure the middle of the middle gameObject is above the ladder so only check x
	case CellKind::longGoDown:
	case CellKind::longGoUpAndDown:
		if (ownerMiddlePos.x >= pCell->middlePos.x - cellSideLenght / 2.f && ownerMiddlePos.x <= pCell->middlePos.x + cellSideLenght / 2.f)
			return true;
		break;
	}

	return false;
}

bool MoveComponent::CanMoveLeft(Cell* pCell, const glm::vec2& ownerMiddlePos)
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
			|| pCell->pLeftNeighbor->cellKind == CellKind::longEmpty || pCell->pLeftNeighbor->cellKind == CellKind::plate) && ownerMiddlePos.x < pCell->middlePos.x)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}

	return false;
}

bool MoveComponent::CanMoveRight(Cell* pCell, const glm::vec2& ownerMiddlePos)
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
			|| pCell->pRightNeighbor->cellKind == CellKind::longEmpty || pCell->pRightNeighbor->cellKind == CellKind::plate) && ownerMiddlePos.x > pCell->middlePos.x)
		{
			return false;
		}
		else
		{
			return true;
		}
		break;
	}

	return false;
}

void MoveComponent::Move(float x, float y)
{
	m_pOwner->SetLocalPosition(x, y);
}
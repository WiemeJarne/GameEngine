#include "BurgerPartComponent.h"
#include "Events.h"
#include "LevelManager.h"
#include "Timer.h"
#include "RenderComponent.h"
#include "EventQueue.h"
#include "CollisionManager.h"
#include "PointsComponent.h"
#include "EngineEvents.h"
#include "Events.h"
#include "EnemyAIComponent.h"
#include <iostream>

BurgerPartComponent::BurgerPartComponent(dae::GameObject* owner, float fallSpeed)
	: Component(owner)
	, m_FallSpeed{ fallSpeed }
{
	//get the RenderComponent from the owner
	auto renderComponent{ owner->GetComponent<RenderComponent>() };

	//if there is a renderComponent get use the textureComponent to set m_Width and m_Height
	if (renderComponent)
	{
		//get the texture component
		auto textureComponent{ renderComponent->GetTextureComponent() };

		//get the size of the texture
		auto textureSize{ textureComponent->GetSize() };

		//set the member variables m_Width and m_Height
		m_Width = static_cast<float>(textureSize.x);
		m_Height = static_cast<float>(textureSize.y);
	}

	dae::EventQueue::GetInstance().AddListener(this);
}

BurgerPartComponent::~BurgerPartComponent()
{
	dae::EventQueue::GetInstance().RemoveListener(this);
}

void BurgerPartComponent::Update()
{
	if (m_HasReachedPlate)
		return;

	//when all the parts have been walked over or m_StartFalling is true because another burgerpart hit this one the burgerPart has to fall
	if ((m_FirstQuarterWalkedOver && m_SecondWalkedOver && m_ThirdWalkedOver && m_FourthWalkedOver || m_IsFalling))
	{
		m_IsFalling = true;

		//get the pos of the owner of this component
		auto ownerPos{ m_pOwner->GetLocalPos() };

		//calculate the middle of the owner of this component on x-axis only (this is to find the correct cell the owner of the gameObject is in
		auto ownerXMiddlePos{ ownerPos };
		ownerXMiddlePos.x += m_Width / 2.f;

		//get the cell the owner of this component is in
		m_pCell = LevelManager::GetInstance().GetActiveLevelGrid()->GetCell(ownerXMiddlePos);

		//check if the owner is now in another cell
		if (m_pCell && m_pPreviousCell && (m_pCell != m_pPreviousCell) && !m_ShouldFallUntilPlatform)
		{
			//if so check if it is a cell with a long platform
			switch (m_pCell->cellKind)
			{
			case CellKind::plate:
				m_HasReachedPlate = true;
				dae::EventQueue::GetInstance().AddEvent(std::any(), static_cast<int>(Event::burgerPartReachedPlate), false);
			case CellKind::longFloor:
			case CellKind::longGoDown:
			case CellKind::longGoUp:
			case CellKind::longGoUpAndDown:
				//if so keep moving until the bottom is at the platform
				m_ShouldFallUntilPlatform = true;
				m_ToGoYValue = m_pCell->middlePos.y;
				if(!m_HasReachedPlate)
				dae::EventQueue::GetInstance().AddEvent(std::any(), static_cast<int>(Event::burgerPartDropped1Level), false);
				break;
			}
		}

		m_pPreviousCell = m_pCell;

		if (m_ShouldFallUntilPlatform && m_pCell)
		{
			//check if the platform has been reached
			if (abs(ownerPos.y - m_pCell->middlePos.y) < 0.3f) //the 0.3f is because of the speed it is possible that ownerPos.y will never be close enough to m_ToGoYValue
			{
				m_ShouldFallUntilPlatform = false;
				m_IsFalling = false;
				m_FirstQuarterWalkedOver = false;
				m_SecondWalkedOver = false;
				m_ThirdWalkedOver = false;
				m_FourthWalkedOver = false;
				m_IsFalling = false;
				return;
			}
		}

		//calculate new pos
		auto newPos{ m_pOwner->GetLocalPos() };
		newPos.y += m_FallSpeed * Timer::GetInstance().GetElapsedSec();

		m_pOwner->SetLocalPosition(newPos.x, newPos.y);
	}
}

void BurgerPartComponent::OnNotify(std::any data, int eventId, bool isEngineEvent)
{
	if (!isEngineEvent)
		return;

	if (eventId != static_cast<int>(dae::EngineEvents::collisionEvent))
	return;

	dae::CollidedGameObjects collidedGameObjects{};

	if(data.type() == typeid(dae::CollidedGameObjects))
	{ 
		collidedGameObjects = std::any_cast<dae::CollidedGameObjects>(data);
	}
	else return;

	//check if the triggered object is this component parent if not return
	if (collidedGameObjects.pTriggered != m_pOwner)
		return;

	//check if the trigger object is a player this is done by checking if the gameObject has a pointsComponent
	bool hasOtherBurgerPartComponent{ collidedGameObjects.pOther->HasComponent<BurgerPartComponent>() };
	if (!collidedGameObjects.pOther->HasComponent<EnemyAIComponent>() && !hasOtherBurgerPartComponent)
		CalculateWalkedOver(collidedGameObjects.pOther);

	//if pData is not a player check if it is another burger part by checking if the gameObject has a BurgerPartComponent
	else if (hasOtherBurgerPartComponent)
		CollidedWithOtherBurgerPart(collidedGameObjects.pOther);
}

void BurgerPartComponent::CalculateWalkedOver(dae::GameObject* pGameObject)
{
	//get the pos of the owner of this component
	auto ownerPos{ m_pOwner->GetLocalPos() };

	//calculate the middle of the owner of this component on x-axis only (this is to find the correct cell the owner of the gameObject is in
	auto ownerXMiddlePos{ ownerPos };
	ownerXMiddlePos.x += m_Width / 2.f;

	//get the pos of the given game object
	auto goPos{ pGameObject->GetLocalPos() };

	//calculate the middle of the given GameObject
	goPos.x += 8.f;

	//get the active grid
	auto pActiveGrid{ LevelManager::GetInstance().GetActiveLevelGrid() };

	//get the cell the owner of this component is in
	auto pOwnerCell{ pActiveGrid->GetCell(ownerXMiddlePos) };

	//get the cell the given game object is is
	auto pGoCell{ pActiveGrid->GetCell(goPos) };

	if (!pOwnerCell || !pGoCell)
		return;

	//if they are not in the same row they don't thouch each other so return
	if (pOwnerCell->rowNr != pGoCell->rowNr)
		return;

	//if they are in the same row check how far the given gameObject is in the first quarter of this gameObject
	if (goPos.x > ownerPos.x && goPos.x < ownerPos.x + m_Width / 4.f)
	{
		m_FirstQuarterWalkedOver = true;
		return;
	}

	//check if the given gameObject is in the second quarter of this gameObject
	if (goPos.x > ownerPos.x + m_Width / 4.f && goPos.x < ownerPos.x + m_Width / 2.f)
	{
		m_SecondWalkedOver = true;
		return;
	}

	//check if the given gameObject is in the third quarter of this gameObject
	if (goPos.x > ownerPos.x + m_Width / 2.f && goPos.x < ownerPos.x + 3 * m_Width / 4.f)
	{
		m_ThirdWalkedOver = true;
		return;
	}

	//check if the given gameObject is in the fourth quarter of this gameObject
	if (goPos.x > ownerPos.x + 3 * m_Width / 4.f && goPos.x < ownerPos.x + m_Width)
	{
		m_FourthWalkedOver = true;
		return;
	}
}

void BurgerPartComponent::CollidedWithOtherBurgerPart(dae::GameObject* pGameObject)
{
	//get the burgerPartComponent of the colliding gameObject
	auto pOtherBurgerPartComponent{ pGameObject->GetComponent<BurgerPartComponent>() };

	//check if this burgerPart is above the other burgerPart
	if (m_pOwner->GetLocalPos().y < pGameObject->GetLocalPos().y)
	{
		//check if the other bugerPart has reached a plate
		if (pOtherBurgerPartComponent->GetHasReachedPlate() && m_HasReachedPlate != true)
		{
			m_HasReachedPlate = true; //if so then is object also reached a plate
			dae::EventQueue::GetInstance().AddEvent(std::any(), static_cast<int>(Event::burgerPartReachedPlate), false);
		}
	}
	else //if this burgerPart is not above the other burgerPart (so it is below) then start with falling unless this burgerPart already is on a plate
	{
		if(!m_HasReachedPlate)
			m_IsFalling = true;
	}
}
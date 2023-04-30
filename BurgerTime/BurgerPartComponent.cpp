#include "BurgerPartComponent.h"
#include "Events.h"
#include "LevelGrid.h"
#include "Timer.h"
#include "RenderComponent.h"
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
}

void BurgerPartComponent::Update()
{
	//when all the parts have been walked over the burgerPart has to fall
	if (m_FirstQuarterWalkedOver && m_SecondWalkedOver && m_ThirdWalkedOver && m_FourthWalkedOver)
	{
		//get the pos of the owner of this component
		auto ownerPos{ m_pOwner->GetLocalPos() };

		//calculate the middle of the owner of this component on x-axis only (this is to find the correct cell the owner of the gameObject is in
		auto ownerXMiddlePos{ ownerPos };
		ownerXMiddlePos.x += m_Width / 2.f;

		//get the cell the owner of this component is in
		m_pCell = LevelGrid::GetInstance().GetCell(ownerXMiddlePos);

		//check if the owner is now in another cell
		if (m_pCell && m_pPreviousCell && (m_pCell != m_pPreviousCell) && !m_ShouldFallUntilPlatform)
		{
			//if so check if it is a cell with a long platform
			switch (m_pCell->cellKind)
			{
			case CellKind::plate:
				m_HasReachedPlate = true;
			case CellKind::longFloor:
			case CellKind::longGoDown:
			case CellKind::longGoUp:
			case CellKind::longGoUpAndDown:
				//if so keep moving until the bottom is at the platform
				m_ShouldFallUntilPlatform = true;
				m_ToGoYValue = m_pCell->middlePos.y;
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
				m_FirstQuarterWalkedOver = false;
				m_SecondWalkedOver = false;
				m_ThirdWalkedOver = false;
				m_FourthWalkedOver = false;
				return;
			}
		}

		//calculate new pos
		auto newPos{ m_pOwner->GetLocalPos() };
		newPos.y += m_FallSpeed * Timer::GetInstance().GetElapsedSec();

		m_pOwner->SetLocalPosition(newPos.x, newPos.y);
	}
}

void BurgerPartComponent::OnNotify(dae::GameObject* go, int eventId)
{
	if (eventId == static_cast<int>(Events::gameObjectMoved))
	{
		//get the pos of the owner of this component
		auto ownerPos{ m_pOwner->GetLocalPos() };

		//calculate the middle of the owner of this component on x-axis only (this is to find the correct cell the owner of the gameObject is in
		auto ownerXMiddlePos{ ownerPos };
		ownerXMiddlePos.x += m_Width / 2.f;

		//get the pos of the given game object
		auto goPos{ go->GetLocalPos() };

		//calculate the middle of the given GameObject
		goPos.x += 8.f;

		//get the cell the owner of this component is in
		auto pOwnerCell{ LevelGrid::GetInstance().GetCell(ownerXMiddlePos) };

		//get the cell the given game object is is
		auto pGoCell{ LevelGrid::GetInstance().GetCell(goPos) };

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
}
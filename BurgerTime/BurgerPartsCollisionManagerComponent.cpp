#include "BurgerPartsCollisionManagerComponent.h"
#include <iostream>

BurgerPartsCollisionManagerComponent::BurgerPartsCollisionManagerComponent(dae::GameObject* owner)
	: Component(owner)
{}

void BurgerPartsCollisionManagerComponent::Update()
{
	//remove all the burgerPartComponents from the vector that are nullptr
	m_BurgerPartComponents.erase(std::remove(m_BurgerPartComponents.begin(), m_BurgerPartComponents.end(), nullptr), m_BurgerPartComponents.end());

	//check of there are BurgerParts overlapping
	for (auto pBurgerPartComponent : m_BurgerPartComponents)
	{
		for (auto pOtherBurgerPartComponent : m_BurgerPartComponents)
		{
			//make sure the check is not done on the same BurgerPartComponent
			if (pBurgerPartComponent == pOtherBurgerPartComponent)
				continue;

			//check if the burgerParts are overlapping
			if (AreBurgerpartsOverlapping(pBurgerPartComponent->GetTopLeftPos(), pBurgerPartComponent->GetWidth(), pBurgerPartComponent->GetHeight(),
				pOtherBurgerPartComponent->GetTopLeftPos(), pOtherBurgerPartComponent->GetWidth(), pOtherBurgerPartComponent->GetHeight()))
			{
				//check which burgerPart is at the bottom an drop that one unless the bottom burgerPart has reached the plate
				if (pBurgerPartComponent->GetTopLeftPos().y < pOtherBurgerPartComponent->GetTopLeftPos().y)
				{
					//check if pOtherBurgerPartComponent has reached the plate if so then pBurgerPartComponent has also reached the plate and none of them should move
					if (pOtherBurgerPartComponent->GetHasReachedPlate())
					{
						pBurgerPartComponent->SetHasReachedPlate(true);
					}
					else
						pOtherBurgerPartComponent->SetStartFalling(true);
				}
				else
				{
					//check if pBurgerPartComponent has reached the plate if so then pOtherBurgerPartComponent has also reached the plate and none of them should move
					if (pBurgerPartComponent->GetHasReachedPlate())
					{
						pOtherBurgerPartComponent->SetHasReachedPlate(true);
					}
					else
					{
						pBurgerPartComponent->SetStartFalling(true);
					}
				}
			}
		}
	}
}

void BurgerPartsCollisionManagerComponent::AddBurgerPartComponent(BurgerPartComponent* pBurgerPartComponent)
{
	//check if this component has already been added
	for (const auto pBurgerPart : m_BurgerPartComponents)
	{
		if (pBurgerPart == pBurgerPartComponent)
			return;
	}

	m_BurgerPartComponents.push_back(pBurgerPartComponent);
}

bool BurgerPartsCollisionManagerComponent::AreBurgerpartsOverlapping(const glm::vec2& part1TopLeftPos, float part1Width, float part1Height, const glm::vec2& part2TopLeftPos, float part2Width, float part2Height)
{
	//if one rectangle is to the left side of the other they are not overlapping
	if (part1TopLeftPos.x > (part2TopLeftPos.x + part2Width) || part2TopLeftPos.x > (part1TopLeftPos.x + part1Width))
		return false;

	//if one rectangle is above the other they are not overlapping
	if ((part1TopLeftPos.y + part1Height) < part2TopLeftPos.y || (part2TopLeftPos.y + part2Height) < part1TopLeftPos.y)
		return false;

	return true;
}
#include "BurgerPartsCollisionManagerComponent.h"

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
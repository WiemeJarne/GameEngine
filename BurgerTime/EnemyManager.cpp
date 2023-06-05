#include "EnemyManager.h"
#include <iostream>

EnemyManagerComponent::EnemyManagerComponent(dae::GameObject* pOwner)
	: Component(pOwner)
{}

void EnemyManagerComponent::Update()
{
	int newAmountOfChildObjects{ static_cast<int>(m_pOwner->GetChildCount()) };
	if (m_AmountOfChildObjectsCheckForHealthComponent != newAmountOfChildObjects)
	{
		//get the health components of the new added children (if they have it)
		for (int index{ m_AmountOfChildObjectsCheckForHealthComponent }; index < newAmountOfChildObjects; ++index)
		{
			//get the child
			auto pChild{ m_pOwner->GetChildAt(index) };

			//get the healthComponent of the child
			auto childHealthComponent{ pChild->GetComponent<HealthComponent>() };

			//check if the childHealthComponent exists
			if (childHealthComponent)
			{
				//if so get add it to the enemyHealthComponent vector and add the child to the enemy vector
				m_Enemies.push_back(std::pair<dae::GameObject*, HealthComponent*>(pChild, childHealthComponent));
				++m_AmountOfChildObjectsCheckForHealthComponent;
			}
		}
	}

	//loop over the enemies
	for (auto& enemyPair : m_Enemies)
	{
		//check if the enemy has zero health and if they still have a parent
		if (enemyPair.second->GetHealth() == 0.f)
		{
			enemyPair.first->SetLocalPosition(-100.f, 0.f);
			
			if (enemyPair.second->GetSecSinceDeath() >= 3.f)
			{
				enemyPair.first->SetLocalPosition(100.f, 0.f);
			}
		}
	}
}
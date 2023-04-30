#include "LadderCollisionComponent.h"
#include "Events.h"
#include <iostream>

LadderCollisionComponent::LadderCollisionComponent(dae::GameObject* owner)
	: Component(owner)
{}

void LadderCollisionComponent::OnNotify(dae::GameObject* pData, int eventId)
{
	if (eventId == static_cast<int>(Events::playerMoved))
	{
		//calculate the middle of the player
		glm::vec2 playerMiddlePos{ pData->GetLocalPos() };
		playerMiddlePos.x += 16.f;
		playerMiddlePos.y += 16.f;

		//get the pos of the owner of this component
		glm::vec2 ownerPos{ m_pOwner->GetLocalPos() };

		//check if the middle of the player is in this collision box if so move the player up
		if (playerMiddlePos.x > ownerPos.x && playerMiddlePos.x < (ownerPos.x + 16.f)
			&& playerMiddlePos.y > (ownerPos.y + 6.f) && playerMiddlePos.y < ownerPos.y)
		{
			std::cout << "ladder\n";
		}
	}
}
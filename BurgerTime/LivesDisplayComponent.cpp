#include "LivesDisplayComponent.h"
#include "Events.h"

LivesDisplayComponent::LivesDisplayComponent(dae::GameObject* owner, HealthComponent* pHealthComponent, dae::TextComponent* pTextComponent)
	: Component(owner)
	, m_pTextComponent{ pTextComponent }
{	
	if (m_pTextComponent && pHealthComponent)
	{
		m_pTextComponent->SetText("lives: " + std::to_string(pHealthComponent->GetHealth()));
	}
}

void LivesDisplayComponent::OnNotify(HealthComponent* pData, int eventId)
{
	if(eventId == static_cast<int>(Event::playerLostLife))
		m_pTextComponent->SetText("lives: " + std::to_string(pData->GetHealth()));
}
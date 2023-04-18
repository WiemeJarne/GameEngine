#include "PointsDisplayComponent.h"

PointsDisplayComponent::PointsDisplayComponent(dae::GameObject* owner, PointsComponent* pPointsComponent, dae::TextComponent* pTextComponent)
	: Component(owner)
	, m_pTextComponent{ pTextComponent }
{
	if (m_pTextComponent && pPointsComponent)
	{
		pPointsComponent->AddObserver(this);
		m_pTextComponent->SetText("points: " + std::to_string(pPointsComponent->GetPoints()));
	}
}

void PointsDisplayComponent::OnNotify(PointsComponent* pData, Events event)
{
	switch (event)
	{
	case Events::playerEarnedPoint:
		m_pTextComponent->SetText("points: " + std::to_string(pData->GetPoints()));
		break;
	}
}
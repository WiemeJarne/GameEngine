#include "PointsComponent.h"
#include "Events.h"
#include "ResourceManager.h"
#include "EventQueue.h"

PointsComponent::PointsComponent(dae::GameObject* owner)
	: Component(owner)
{
	auto textComponent{ owner->GetComponent<dae::TextComponent>() };

	if (textComponent)
	{
		m_pTextComponent = textComponent;
	}
	else
	{
		auto font{ dae::ResourceManager::GetInstance().LoadFont("PressStart2P-vaV7.ttf", 12) };
		auto newTextComponent{ std::make_unique<dae::TextComponent>(owner, "0", font) };
		m_pTextComponent = newTextComponent.get();
		owner->AddComponent(std::move(newTextComponent));
	}

	dae::EventQueue::GetInstance().AddListener(this);
}

PointsComponent::~PointsComponent()
{
	dae::EventQueue::GetInstance().RemoveListener(this);
}

void PointsComponent::OnNotify(std::any data, int eventId, bool isEngineEvent)
{
	if (isEngineEvent)
		return;

	Event event{ static_cast<Event>(eventId) };

	switch (event)
	{
	case Event::burgerPartDropped1Level:
		m_AmountOfPoints += 50;
		m_pTextComponent->SetText(std::to_string(m_AmountOfPoints));
		break;
	}
}
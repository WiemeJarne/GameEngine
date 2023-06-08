#include "PointsComponent.h"
#include "Events.h"
#include "ResourceManager.h"
#include "EventQueue.h"
#include "TextureComponent.h"
#include <iostream>

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
	case Event::burgerPartReachedPlate:
		m_AmountOfPoints += 50;
		m_pTextComponent->SetText(std::to_string(m_AmountOfPoints));
		break;

	case Event::burgerPartDroppedWith1EnemyOn:
		m_AmountOfPoints += 500;
		break;

	case Event::burgerPartDroppedWith2EnemiesOn:
		m_AmountOfPoints += 1000;
		break;

	case Event::burgerPartDroppedWith3EnemiesOn:
		m_AmountOfPoints += 2000;
		break;

	case Event::burgerPartDroppedWith4EnemiesOn:
		m_AmountOfPoints += 4000;
		break;

	case Event::burgerPartDroppedWith5EnemiesOn:
		m_AmountOfPoints += 8000;
		break;

	case Event::burgerPartDroppedWith6EnemiesOn:
		m_AmountOfPoints += 16000;
		break;
	case Event::enemyDied:
		auto pTextureComponent{ std::any_cast<dae::TextureComponent*>(data) };

		if (!pTextureComponent)
			return;

		//get the texture file name
		const std::string& textureFileName{ pTextureComponent->GetFileName() };

		if (textureFileName == "MrHotDog.png")
			m_AmountOfPoints += 100;
		else if (textureFileName == "MrPickle.png")
			m_AmountOfPoints += 200;
		else if (textureFileName == "MrEgg.png")
			m_AmountOfPoints += 300;

		break;
	}
}

void PointsComponent::AddPoints(int amount)
{
	m_AmountOfPoints += amount;
	m_pTextComponent->SetText(std::to_string(m_AmountOfPoints));
}

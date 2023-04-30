#include "PointsComponent.h"
#include "Events.h"

PointsComponent::PointsComponent(dae::GameObject* owner)
	: Component(owner)
{}

void PointsComponent::AddPoints(int amount)
{
	m_AmountOfPoints += amount;

	Notify(this, static_cast<int>(Events::playerEarnedPoint));
}
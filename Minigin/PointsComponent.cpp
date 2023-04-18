#include "PointsComponent.h"

PointsComponent::PointsComponent(dae::GameObject* owner)
	: Component(owner)
{}

void PointsComponent::AddPoints(int amount)
{
	m_AmountOfPoints += amount;

	Notify(this, Events::playerEarnedPoint);
}
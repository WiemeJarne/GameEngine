#pragma once
#include "Component.h"
#include "Subject.h"

class PointsComponent : public Component, public Subject<PointsComponent>
{
public:
	PointsComponent() = default;
	PointsComponent(dae::GameObject* owner);
	~PointsComponent() = default;
	PointsComponent(const PointsComponent& other) = delete;
	PointsComponent(PointsComponent&& other) = delete;
	PointsComponent& operator=(const PointsComponent& other) = delete;
	PointsComponent& operator=(PointsComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	void AddPoints(int amount);
	int GetPoints() const { return m_AmountOfPoints; }

private:
	int m_AmountOfPoints{};
};
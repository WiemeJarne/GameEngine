#pragma once
#include "Component.h"
#include "EventListener.h"
#include "TextComponent.h"

class PointsComponent : public Component, public dae::EventListener
{
public:
	PointsComponent() = default;
	PointsComponent(dae::GameObject* owner);
	~PointsComponent();
	PointsComponent(const PointsComponent& other) = delete;
	PointsComponent(PointsComponent&& other) = delete;
	PointsComponent& operator=(const PointsComponent& other) = delete;
	PointsComponent& operator=(PointsComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(std::any data, int eventId, bool isEngineEvent) override;
	int GetPoints() const { return m_AmountOfPoints; }
	void AddPoints(int amount);

private:
	int m_AmountOfPoints{};
	dae::TextComponent* m_pTextComponent{};
};
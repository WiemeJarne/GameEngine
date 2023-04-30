#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "PointsComponent.h"
#include "Observer.h"

class PointsDisplayComponent final : public Component, public Observer<PointsComponent>
{
public:
	PointsDisplayComponent(dae::GameObject* owner, PointsComponent* pPointsComponent, dae::TextComponent* pTextComponent);
	~PointsDisplayComponent() = default;
	PointsDisplayComponent(const PointsDisplayComponent& other) = delete;
	PointsDisplayComponent(PointsDisplayComponent&& other) = delete;
	PointsDisplayComponent& operator=(const PointsDisplayComponent& other) = delete;
	PointsDisplayComponent& operator=(PointsDisplayComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(PointsComponent* pData, int event) override;

private:
	dae::TextComponent* m_pTextComponent{};

};
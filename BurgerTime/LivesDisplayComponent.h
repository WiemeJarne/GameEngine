#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "Observer.h"

class LivesDisplayComponent : public Component, public Observer<HealthComponent>
{
public:
	LivesDisplayComponent(dae::GameObject* owner, HealthComponent* pHealthComponent, dae::TextComponent* pTextComponent);
	~LivesDisplayComponent() = default;
	LivesDisplayComponent(const LivesDisplayComponent& other) = delete;
	LivesDisplayComponent(LivesDisplayComponent&& other) = delete;
	LivesDisplayComponent& operator=(const LivesDisplayComponent& other) = delete;
	LivesDisplayComponent& operator=(LivesDisplayComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(HealthComponent* pData, int eventId) override;

private:
	dae::TextComponent* m_pTextComponent{};
};
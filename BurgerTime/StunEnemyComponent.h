#pragma once
#include "Component.h"
#include "EventListener.h"

class StunEnemyComponent final : public dae::Component, public dae::EventListener
{
public:
	StunEnemyComponent(dae::GameObject* pOwner, float amountOfSecStunned, float amountOfSecAlive);
	~StunEnemyComponent();

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(std::any data, int eventId, bool isEngineEvent) override;

private:
	const float m_AmountOfSecStunned{};
	const float m_AmountOfSecAlive{};
	float m_AmountOfSecSinceSpawned{};
};
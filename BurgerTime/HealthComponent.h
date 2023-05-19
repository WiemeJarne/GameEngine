#pragma once
#include "Component.h"
#include "EventListener.h"

class HealthComponent : public Component, public dae::EventListener
{
public:
	HealthComponent(dae::GameObject* owner, int amountOfLives, bool isPlayer = true);
	~HealthComponent() = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(std::any data, int eventId, bool isEngineEvent) override;
	void Damage(int amount);
	void Heal(int amount);
	void Reset();
	int GetHealth() const { return m_AmountOfLives; }

private:
	int m_StartAmountOfLives{};
	int m_AmountOfLives{};
	float m_SecSinceDeath{};
	const bool m_IsOwnerPlayer{};
};
#pragma once
#include "Component.h"
#include "Subject.h"

class HealthComponent : public Component, public Subject<HealthComponent>
{
public:
	HealthComponent(dae::GameObject* owner, int amountOfLives);
	~HealthComponent() = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	void Damage(int amount);
	int GetHealth() const { return m_AmountOfLives; }

private:
	int m_AmountOfLives{};
};
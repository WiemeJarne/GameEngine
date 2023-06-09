#pragma once
#include "Component.h"
#include "EventListener.h"
#include <glm/vec2.hpp>
#include <string>
#include <vector>

class HealthComponent : public Component, public dae::EventListener
{
public:
	HealthComponent(dae::GameObject* owner, int amountOfLives, bool isPlayer = true);
	HealthComponent(dae::GameObject* owner, int amountOfLives, const glm::vec2& visualizationPos, const std::string& textureFilePath, bool isPlayer = true);
	~HealthComponent();
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) = delete;

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(std::any data, int eventId, bool isEngineEvent) override;
	void Damage(int amount, bool shouldBreadCastDieEvent = true);
	void Reset();
	void VisualizeHealth(const glm::vec2& pos, const std::string& textureFilePath);
	void Die();
	int GetHealth() const { return m_AmountOfLives; }
	float GetSecSinceDeath() const { return m_SecSinceDeath; }

private:
	int m_StartAmountOfLives{};
	int m_AmountOfLives{};
	float m_SecSinceDeath{};
	const bool m_IsOwnerPlayer{};
	std::vector<dae::GameObject*> m_pVisualizeGameObjects;
	float m_SecSinceLiveLost{};
};
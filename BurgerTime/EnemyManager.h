#pragma once
#include "GameObject.h"
#include "HealthComponent.h"
#include "Component.h"
#include <vector>

class EnemyManagerComponent final : public Component
{
public:
	EnemyManagerComponent(dae::GameObject* pOwner);

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}

private:
	int m_AmountOfChildObjectsCheckForHealthComponent{};
	std::vector<std::pair<dae::GameObject*, HealthComponent*>> m_Enemies{};
};
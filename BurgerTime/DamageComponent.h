#pragma once
#include "Component.h"
#include "GameObject.h"

class DamageComponent final : public Component
{
public:
	DamageComponent(dae::GameObject* pOwner, int damageAmount);

	void Update() {}
	void Render() const {}
	void RenderImGui() {}

	int GetDamageAmount() const { return m_DamageAmount; }

private:
	int m_DamageAmount;
};
#pragma once
#include "Component.h"
#include "BurgerPartComponent.h"
#include <vector>

class BurgerPartsCollisionManagerComponent final : public Component
{
public: 
	BurgerPartsCollisionManagerComponent(dae::GameObject* owner);

	virtual ~BurgerPartsCollisionManagerComponent() = default;
	BurgerPartsCollisionManagerComponent(const BurgerPartsCollisionManagerComponent&) = delete;
	BurgerPartsCollisionManagerComponent(BurgerPartsCollisionManagerComponent&&) = delete;
	BurgerPartsCollisionManagerComponent& operator=(const BurgerPartsCollisionManagerComponent&) = delete;
	BurgerPartsCollisionManagerComponent& operator=(BurgerPartsCollisionManagerComponent&&) = delete;

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}

	void AddBurgerPartComponent(BurgerPartComponent* pBurgerPartComponent);

private:
	std::vector<BurgerPartComponent*> m_BurgerPartComponents{};
};
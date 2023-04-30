#pragma once
#include "Component.h"
#include "Observer.h"
#include "GameObject.h"

class LadderCollisionComponent : public Component, public Observer<dae::GameObject>
{
public:
	LadderCollisionComponent(dae::GameObject* owner);
	~LadderCollisionComponent() = default;
	LadderCollisionComponent(const LadderCollisionComponent& other) = delete;
	LadderCollisionComponent(LadderCollisionComponent&& other) = delete;
	LadderCollisionComponent& operator=(const LadderCollisionComponent& other) = delete;
	LadderCollisionComponent& operator=(LadderCollisionComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	void OnNotify(dae::GameObject* pData, int eventId) override;
};
#pragma once
#include "Component.h"
#include "MoveComponent.h"
#include "EventListener.h"
#include "glm/vec2.hpp"

class EnemyAIComponent final : public Component, public dae::EventListener
{
public:
	EnemyAIComponent(dae::GameObject* pOwner, float moveSpeed);

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}

	void OnNotify(std::any data, int eventId, bool isEngineEvent);

private:
	MoveComponent* m_pMoveComponent{};
	glm::vec2 m_PlayerMiddlePos{};
	glm::vec2 m_PreviousDirection{};
};
#pragma once
#include "Component.h"
#include "MoveComponent.h"
#include "EventListener.h"
#include "glm/vec2.hpp"

class EnemyAIComponent final : public Component, public dae::EventListener
{
public:
	EnemyAIComponent(dae::GameObject* pOwner, float moveSpeed, bool shouldRandomlyClimbLadder = false, float secBetweenRandomClimbLadder = 5.f, bool shouldRandomlyFlipDirection = false, float secBetweenRandomFlipDirection = 5.f);
	~EnemyAIComponent();

	void Update() override;
	void Render() const override {}
	void RenderImGui() override {}

	void OnNotify(std::any data, int eventId, bool isEngineEvent);

private:
	MoveComponent* m_pMoveComponent{};
	glm::vec2 m_PlayerMiddlePos{};
	glm::vec2 m_PreviousDirection{};
	Cell* m_pClosestLadder{};
	Cell* m_pPreviousClimbedLadder{};
	LevelGrid* m_pActiveGrid{};
	bool m_ShouldRandomlyClimbLadder{};
	const float m_SecBetweenRandomClimbLadder{};
	float m_SecSinceLastRandomClimbedLadder{};
	bool m_ShouldRandomlyFlipDirection{};
	const float m_SecBetweenRandomFlipDirection{};
	float m_SecSinceRandomDirectionFlip{};
	float m_EnemyWidth{};
	float m_EnemyHeight{};

	void MoveTowardsGrid(const glm::vec2& ownerMiddlePos);
	void FlipDirection();
	void RandomlyClimbLadder(Cell* currentCell);

	static glm::vec2 m_sUpDirection;
	static glm::vec2 m_sDownDirection;
	static glm::vec2 m_sLeftDirection;
	static glm::vec2 m_sRightDirection;
};
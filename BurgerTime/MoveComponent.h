#pragma once
#include "Component.h"
#include "LevelGrid.h"
#include "Subject.h"
#include <glm/vec2.hpp>

class MoveComponent : public Component
{
public:
	MoveComponent(dae::GameObject* owner, float moveSpeed, bool isPlayer = true, bool canMoveOverEmptyCells = false);
	~MoveComponent() = default;
	MoveComponent(const MoveComponent& other) = delete;
	MoveComponent(MoveComponent&& other) = delete;
	MoveComponent& operator=(const MoveComponent& other) = delete;
	MoveComponent& operator=(MoveComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	bool Move(const glm::vec2& direction);

private:
	const float m_MoveSpeed{};
	const bool m_IsPlayer{};
	bool m_HasSnappedToPlatform{};
	Cell* m_pPreviousCell{};
	float m_OwnerWidth{};
	float m_OwnerHeight{};
	bool m_CanMoveOverEmptyCells{};

	bool CanMoveUp(Cell* pCell, const glm::vec2& ownerMiddlePos, float cellSideLenght);
	bool CanMoveDown(Cell* pCell, const glm::vec2& ownerMiddlePos, float cellSideLenght);
	bool CanMoveLeft(Cell* pCell, const glm::vec2& ownerMiddlePos);
	bool CanMoveRight(Cell* pCell, const glm::vec2& ownerMiddlePos);
	void Move(float x, float y);
};
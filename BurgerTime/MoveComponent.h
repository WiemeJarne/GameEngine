#pragma once
#include "Component.h"
#include "LevelGrid.h"
#include "Subject.h"
#include <glm/vec2.hpp>

class MoveComponent : public Component, public Subject<dae::GameObject>
{
public:
	MoveComponent(dae::GameObject* owner, float moveSpeed);
	~MoveComponent() = default;
	MoveComponent(const MoveComponent& other) = delete;
	MoveComponent(MoveComponent&& other) = delete;
	MoveComponent& operator=(const MoveComponent& other) = delete;
	MoveComponent& operator=(MoveComponent&& other) = delete;

	void Update() override {}
	void Render() const override {}
	void RenderImGui() override {}
	void Move(const glm::vec2& direction);

private:
	const float m_MoveSpeed{};
	bool m_HasSnappedToPlatform{};
	Cell* m_pPreviousCell{};
};